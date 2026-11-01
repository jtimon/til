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
        // Struct handles: an owned result, borrowed and mut parameters, Str
        // and Bool fields, literal defaults, and a move into the library.
        try (JniLib.JniPerson p = JniLib.jni_person("ada", 36)) {
            System.out.println(JniLib.jni_person_describe(p));
            JniLib.jni_person_birthday(p);
            p.name("grace");
            System.out.println(JniLib.jni_person_describe(p) + " " + p.active());
        }
        try (JniLib.JniPerson d = new JniLib.JniPerson()) {
            System.out.println(d.name() + " " + d.age() + " " + d.active());
        }
        JniLib.JniPerson moved = JniLib.jni_person("x", 5);
        System.out.println(JniLib.jni_person_consume(moved));
        try {
            moved.age();
            System.out.println("moved handle still usable");
        } catch (IllegalStateException e) {
            System.out.println("moved: " + e.getMessage());
        }
        moved.close();
        for (int i = 0; i < 100000; i++) {
            try (JniLib.JniPerson p = JniLib.jni_person("loop", i)) {
                p.name("renamed");
                check(JniLib.jni_person_describe(p).startsWith("renamed:"), "person loop");
            }
            check(JniLib.jni_person_consume(new JniLib.JniPerson()) == 0, "consume loop");
        }
        // mut scalar and Str parameters: one-element arrays written back.
        long[] n = { 41 };
        JniLib.jni_bump(n);
        String[] text = { "ab" };
        JniLib.jni_append(text, "c\u00e9");
        check(text[0].equals("abc\u00e9"), "jni_append");
        boolean[] flag = { true };
        JniLib.jni_flip(flag);
        System.out.println(n[0] + " " + flag[0]);
        try {
            JniLib.jni_bump(new long[0]);
            System.out.println("empty holder accepted");
        } catch (IllegalArgumentException e) {
            System.out.println("holder: " + e.getMessage());
        }
        // Enums: variant constructors, tag(), payload getters.
        try (JniLib.JniShape circle = JniLib.JniShape_Circle(7);
             JniLib.JniShape label = JniLib.JniShape_Label("tag\u00e9");
             JniLib.JniShape empty = JniLib.JniShape_Empty();
             JniLib.JniShape owner = JniLib.JniShape_Owner(JniLib.jni_person("own", 12))) {
            System.out.println(JniLib.jni_shape_area(circle) + " " + JniLib.jni_shape_area(owner) + " "
                + JniLib.jni_shape_area(empty));
            check(label.tag() == JniLib.JniShape.TAG_Label, "label tag");
            check(label.Label().equals("tag\u00e9"), "label payload");
            System.out.println(circle.Circle() + " " + owner.Owner().name() + " " + empty.tag());
            try {
                circle.Label();
                System.out.println("wrong payload read");
            } catch (IllegalStateException e) {
                System.out.println("payload: " + e.getMessage());
            }
        }
        // An own field behind a pointer, and borrowed results.
        try (JniLib.JniHolder h = JniLib.jni_holder("held")) {
            JniLib.JniPerson inner = JniLib.jni_holder_person(h);
            System.out.println(h.count() + " " + h.person().name() + " " + JniLib.jni_holder_name(h));
            inner.name("renamed");
            h.count(5);
            System.out.println(h.count() + " " + h.person().name());
            try {
                JniLib.jni_person_consume(inner);
                System.out.println("moved a borrowed handle");
            } catch (IllegalStateException e) {
                System.out.println("borrowed: " + e.getMessage());
            }
        }
        // Callbacks: Java lambdas called from til.
        System.out.println(JniLib.jni_apply(x -> x * 10, 4));
        System.out.println(JniLib.jni_apply_str(s -> "[" + s + "]", "cb"));
        try (JniLib.JniPerson p = JniLib.jni_person("cbp", 33)) {
            System.out.println(JniLib.jni_apply_person(q -> q.age() + q.name().length(), p));
        }
        System.out.println(JniLib.jni_make(age -> {
            JniLib.JniPerson made = new JniLib.JniPerson();
            made.name("made");
            made.age(age);
            return made;
        }, 9));
        for (int i = 0; i < 100000; i++) {
            check(JniLib.jni_apply(x -> x + 1, i) == 2L * i + 3, "callback loop");
            check(JniLib.jni_apply_str(s -> s + "!", "x").equals("x!"), "str callback loop");
        }
        // Vec(Str) as String[]: in, out, mut, and into a callback.
        System.out.println(JniLib.jni_join(new String[] { "a", "b\u00e9", "c" }, "-").equals("a-b\u00e9-c"));
        System.out.println(String.join("|", JniLib.jni_split("x,y,,z")));
        String[][] parts = { new String[] { "p" } };
        JniLib.jni_push(parts, "q");
        System.out.println(String.join("|", parts[0]));
        System.out.println(JniLib.jni_count(v -> v.length * 100 + v[1].length(), "aa,bbb,c"));
        // Default constructors follow nested constructor calls and box
        // own fields, as til's T() does.
        try (JniLib.JniHolder d = new JniLib.JniHolder()) {
            System.out.println(d.person().name() + " " + d.count());
        }
        for (int i = 0; i < 100000; i++) {
            check(JniLib.jni_split("a,b").length == 2, "split loop");
            check(JniLib.jni_count(v -> v.length, "a,b,c") == 3, "vec callback loop");
            try (JniLib.JniHolder d = new JniLib.JniHolder()) { check(d.count() == 0, "holder loop"); }
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
