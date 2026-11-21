#ifndef TIL_ANDROID_GUI
#error "std/android_jni requires a mode gui Android APK build"
#endif

#include <android/log.h>
#include <android_native_app_glue.h>
#include <stdbool.h>
#include <stdatomic.h>
#include <stdlib.h>
#include <string.h>

extern struct android_app *GetAndroidApp(void);

typedef struct {
    JNIEnv *env;
    ANativeActivity *activity;
    bool attached;
    uint32_t id;
    jobject *refs;
    uint32_t count;
    size_t capacity;
} TilJniFrame;

static _Thread_local TilJniFrame frame;
static atomic_uint_fast64_t next_frame = 1;

static void require_jni(JNIEnv *env, bool ok, const char *operation) {
    if ((*env)->ExceptionCheck(env)) {
        (*env)->ExceptionDescribe(env);
        __android_log_assert("JNI exception", "til", "Android JNI: %s threw", operation);
    }
    if (!ok) __android_log_assert("JNI result", "til", "Android JNI: %s failed", operation);
}

static JNIEnv *current_env(void) {
    if (!frame.env) __android_log_assert("JNI frame", "til", "Android JNI: call outside AndroidJni.with_frame");
    return frame.env;
}

void til_android_jni_enter(void) {
    if (frame.env) __android_log_assert("JNI frame", "til", "Android JNI: nested frames are not supported");
    ANativeActivity *activity = GetAndroidApp()->activity;
    JavaVM *vm = activity->vm;
    void *raw_env = NULL;
    JNIEnv *env = NULL;
    // NativeActivity's own JNIEnv belongs to the UI thread.
    jint status = (*vm)->GetEnv(vm, &raw_env, JNI_VERSION_1_6);
    if (status == JNI_EDETACHED) {
        if ((*vm)->AttachCurrentThread(vm, &env, NULL) != JNI_OK) {
            __android_log_assert("JNI attachment", "til", "Android JNI: cannot attach native thread");
        }
    } else if (status == JNI_OK) {
        env = raw_env;
    } else {
        __android_log_assert("JNI environment", "til", "Android JNI: GetEnv failed (%d)", status);
    }
    uint64_t id = atomic_fetch_add_explicit(&next_frame, 1, memory_order_relaxed);
    require_jni(env, id <= UINT32_MAX, "allocate frame ID");
    jint pushed = (*env)->PushLocalFrame(env, 16);
    require_jni(env, pushed == JNI_OK, "PushLocalFrame");
    frame = (TilJniFrame){.env = env, .activity = activity, .attached = status == JNI_EDETACHED, .id = (uint32_t)id};
}

void til_android_jni_leave(void) {
    JNIEnv *env = current_env();
    (*env)->PopLocalFrame(env, NULL);
    if (frame.attached) {
        JavaVM *vm = frame.activity->vm;
        if ((*vm)->DetachCurrentThread(vm) != JNI_OK) {
            __android_log_assert("JNI attachment", "til", "Android JNI: cannot detach native thread");
        }
    }
    free(frame.refs);
    frame = (TilJniFrame){0};
}

// Tokens never expose JNI pointers. Their frame ID rejects stale and
// cross-thread references even when a later JNI frame reuses its slots.
static uint64_t keep_ref(jobject ref) {
    if (!ref) return 0;
    if (frame.count == UINT32_MAX) __android_log_assert("JNI refs", "til", "Android JNI: too many references");
    if (frame.count == frame.capacity) {
        size_t capacity = frame.capacity ? frame.capacity * 2 : 16;
        jobject *refs = realloc(frame.refs, capacity * sizeof(*refs));
        if (!refs) __android_log_assert("JNI refs", "til", "Android JNI: cannot allocate reference table");
        frame.refs = refs;
        frame.capacity = capacity;
    }
    frame.refs[frame.count++] = ref;
    return (uint64_t)frame.id << 32 | frame.count;
}

static jobject get_ref(uint64_t token, bool nullable) {
    if (nullable && token == 0) return NULL;
    uint32_t slot = (uint32_t)token;
    if ((token >> 32) != frame.id || slot == 0 || slot > frame.count) {
        __android_log_assert("JNI reference", "til", "Android JNI: null or out-of-frame reference");
    }
    return frame.refs[slot - 1];
}

uint64_t til_android_jni_activity(void) {
    current_env();
    return keep_ref(frame.activity->clazz);
}

uint64_t til_android_jni_find_class(const char *name) {
    JNIEnv *env = current_env();
    jclass cls = (*env)->FindClass(env, name);
    require_jni(env, cls != NULL, name);
    return keep_ref(cls);
}

int32_t til_android_jni_static_int(uint64_t token, const char *name) {
    JNIEnv *env = current_env();
    jobject cls = get_ref(token, false);
    jclass class_class = (*env)->FindClass(env, "java/lang/Class");
    require_jni(env, class_class != NULL, "java/lang/Class");
    jboolean is_class = (*env)->IsInstanceOf(env, cls, class_class);
    require_jni(env, is_class, "static_int needs a Class reference");
    (*env)->DeleteLocalRef(env, class_class);
    jfieldID field = (*env)->GetStaticFieldID(env, cls, name, "I");
    require_jni(env, field != NULL, name);
    jint result = (*env)->GetStaticIntField(env, cls, field);
    require_jni(env, true, name);
    return result;
}

static jmethodID method_id(JNIEnv *env, jobject receiver, const char *name, const char *sig) {
    jclass cls = (*env)->GetObjectClass(env, receiver);
    require_jni(env, cls != NULL, "GetObjectClass");
    jmethodID method = (*env)->GetMethodID(env, cls, name, sig);
    require_jni(env, method != NULL, name);
    (*env)->DeleteLocalRef(env, cls);
    return method;
}

uint64_t til_android_jni_call_object(uint64_t token, const char *name, const char *sig, uint64_t arg_token) {
    JNIEnv *env = current_env();
    const char *arg_end = strncmp(sig, "(L", 2) == 0 ? strchr(sig + 2, ';') : NULL;
    const char *ret_end = arg_end && strncmp(arg_end + 1, ")L", 2) == 0 ? strchr(arg_end + 3, ';') : NULL;
    if (!ret_end || arg_end == sig + 2 || ret_end == arg_end + 3 || ret_end[1] != '\0') {
        __android_log_assert("JNI descriptor", "til", "Android JNI: call_object expects (Lclass;)Lclass;, got %s", sig);
    }
    jobject receiver = get_ref(token, false);
    jmethodID method = method_id(env, receiver, name, sig);
    jvalue arg = {.l = get_ref(arg_token, true)};
    if (arg.l) {
        // link_c uses til's allocator in the compact layout; libc strndup
        // would allocate a buffer that this file's free cannot release.
        size_t length = (size_t)(arg_end - (sig + 2));
        char *arg_name = malloc(length + 1);
        if (!arg_name) __android_log_assert("JNI descriptor", "til", "Android JNI: cannot allocate argument class name");
        memcpy(arg_name, sig + 2, length);
        arg_name[length] = '\0';
        jclass expected = (*env)->FindClass(env, arg_name);
        require_jni(env, expected != NULL, arg_name);
        free(arg_name);
        jboolean matches = (*env)->IsInstanceOf(env, arg.l, expected);
        require_jni(env, matches, "call_object argument type");
        (*env)->DeleteLocalRef(env, expected);
    }
    jobject result = (*env)->CallObjectMethodA(env, receiver, method, &arg);
    require_jni(env, true, name);
    return keep_ref(result);
}

int32_t til_android_jni_call_int(uint64_t token, const char *name, const char *sig, int32_t value) {
    JNIEnv *env = current_env();
    if (strcmp(sig, "(I)I") != 0) {
        __android_log_assert("JNI descriptor", "til", "Android JNI: call_int expects (I)I, got %s", sig);
    }
    jobject receiver = get_ref(token, false);
    jmethodID method = method_id(env, receiver, name, sig);
    jvalue arg = {.i = value};
    jint result = (*env)->CallIntMethodA(env, receiver, method, &arg);
    require_jni(env, true, name);
    return result;
}
