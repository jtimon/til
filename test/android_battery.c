#include <android/log.h>
#include <android_native_app_glue.h>
#include <stdbool.h>

extern struct android_app *GetAndroidApp(void);

static void require_jni(JNIEnv *env, bool ok, const char *operation) {
    if ((*env)->ExceptionCheck(env)) {
        (*env)->ExceptionDescribe(env);
        __android_log_assert("JNI exception", "TilAndroidSmoke", "%s threw", operation);
    }
    if (!ok) __android_log_assert("JNI result", "TilAndroidSmoke", "%s failed", operation);
}

int32_t android_battery_capacity(void) {
    // NativeActivity owns vm and clazz. Its glue starts this pthread;
    // activity->env belongs to the Android UI thread and cannot be used here.
    ANativeActivity *activity = GetAndroidApp()->activity;
    JavaVM *vm = activity->vm;
    JNIEnv *env = NULL;
    void *attached_env = NULL;
    if ((*vm)->GetEnv(vm, &attached_env, JNI_VERSION_1_6) != JNI_EDETACHED ||
        (*vm)->AttachCurrentThread(vm, &env, NULL) != JNI_OK) {
        __android_log_assert("attach", "TilAndroidSmoke", "cannot attach NativeActivity worker to ART");
    }

    jclass battery = (*env)->FindClass(env, "android/os/BatteryManager");
    require_jni(env, battery != NULL, "BatteryManager class lookup");
    jclass context = (*env)->FindClass(env, "android/content/Context");
    require_jni(env, context != NULL, "Context class lookup");
    jmethodID get_service = (*env)->GetMethodID(env, context, "getSystemService", "(Ljava/lang/Class;)Ljava/lang/Object;");
    require_jni(env, get_service != NULL, "Context.getSystemService lookup");
    jobject manager = (*env)->CallObjectMethod(env, activity->clazz, get_service, battery);
    require_jni(env, manager != NULL, "Context.getSystemService(BatteryManager.class)");

    jfieldID property = (*env)->GetStaticFieldID(env, battery, "BATTERY_PROPERTY_CAPACITY", "I");
    require_jni(env, property != NULL, "BATTERY_PROPERTY_CAPACITY lookup");
    jint capacity_id = (*env)->GetStaticIntField(env, battery, property);
    require_jni(env, true, "BATTERY_PROPERTY_CAPACITY read");
    jmethodID get_property = (*env)->GetMethodID(env, battery, "getIntProperty", "(I)I");
    require_jni(env, get_property != NULL, "BatteryManager.getIntProperty lookup");
    jint capacity = (*env)->CallIntMethod(env, manager, get_property, capacity_id);
    require_jni(env, true, "BatteryManager.getIntProperty(CAPACITY)");

    // Detach releases the local references on this native-only thread.
    if ((*vm)->DetachCurrentThread(vm) != JNI_OK) {
        __android_log_assert("detach", "TilAndroidSmoke", "cannot detach NativeActivity worker from ART");
    }
    return capacity;
}

void android_battery_report(int32_t capacity) {
    __android_log_print(ANDROID_LOG_INFO, "TilAndroidSmoke", "BatteryManager capacity: %d", capacity);
}
