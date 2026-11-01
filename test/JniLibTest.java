// JVM caller for the generated JNI binding of test/jni_lib.til; run by
// `bin/til run test/jni.til jvm`. Non-ASCII round trips are checked with
// equals() so the result does not depend on the JVM's stdout encoding.
import til.jni_lib.JniLib;

public class JniLibTest {
    static void check(boolean ok, String what) {
        if (!ok) throw new AssertionError(what);
    }

    public static void main(String[] args) throws Exception {
        System.out.println(JniLib.jni_add_i8((byte)100, (byte)27));
        System.out.println(Byte.toUnsignedInt(JniLib.jni_add_u8((byte)200, (byte)50)));
        System.out.println(JniLib.jni_add_i16((short)1000, (short)-3000));
        System.out.println(Short.toUnsignedInt(JniLib.jni_add_u16((short)60000, (short)5000)));
        System.out.println(JniLib.jni_add_i32(2000000000, -1));
        System.out.println(Integer.toUnsignedString(JniLib.jni_add_u32(-2, 1)));
        System.out.println(JniLib.jni_add_i64(1L << 40, 7));
        System.out.println(Long.toUnsignedString(JniLib.jni_add_u64(-2L, 1)));
        System.out.println(JniLib.jni_add_usize(40, 2));
        System.out.println(JniLib.jni_half_f32(3.0f));
        System.out.println(JniLib.jni_half_f64(5.0));
        System.out.println(JniLib.jni_not(true) + " " + JniLib.jni_not(false));
        System.out.println(JniLib.JniCounter_twice(21));
        System.out.println(JniLib.jni_str_len("héllo"));
        check(JniLib.jni_greet("wörld").equals("hello, wörld"), "jni_greet");
        System.out.println(JniLib.jni_greet("jvm"));
        System.out.println(JniLib.jni_take("owned"));
        JniLib.jni_noop();
        System.out.println(JniLib.jni_safe_div(84, 2));
        try {
            JniLib.jni_safe_div(1, 0);
            System.out.println("no throw");
        } catch (JniLib.TilError e) {
            System.out.println("caught " + e.type() + " / " + e.getMessage());
        }
        try {
            JniLib.jni_safe_div(1, -1);
            System.out.println("no throw");
        } catch (JniLib.TilError e) {
            System.out.println("caught " + e.type() + " / " + e.getMessage());
        }
        // Repeated calls: borrowed temporaries, owned boxes and results are
        // all released by the bridge or the library, never by the JVM.
        for (int i = 0; i < 100000; i++) {
            check(JniLib.jni_greet("x").length() == 8, "jni_greet loop");
            check(JniLib.jni_take("y").equals("<y>"), "jni_take loop");
        }
        System.out.println("loop ok");
    }
}
