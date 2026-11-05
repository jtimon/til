// JVM caller for the generated JNI binding of test/jni_lib.til; run by
// test/jni.til. Non-ASCII round trips are checked with
// equals() so the result does not depend on the JVM's stdout encoding.
import java.util.Arrays;
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
        // Vec of scalars as primitive arrays, Vec of structs as handle arrays.
        System.out.println(JniLib.jni_sum(new long[] { 1, 2, 3, 40 }));
        System.out.println(Arrays.toString(JniLib.jni_range(5)) + " " + JniLib.jni_range(0).length);
        double[][] ds = { new double[] { 1.5, 2.0 } };
        JniLib.jni_scale(ds, 2.0);
        System.out.println(Arrays.toString(ds[0]));
        System.out.println(JniLib.jni_flags(new boolean[] { true, false, true }));
        JniLib.JniPerson[] ps = JniLib.jni_people(new String[] { "a", "bb", "ccc" });
        System.out.println(ps.length + " " + ps[2].name() + " " + ps[2].age() + " " + JniLib.jni_oldest(ps));
        // own: the library gets clones; the Java handles stay the caller's.
        System.out.println(JniLib.jni_adopt(ps) + " " + ps[0].name());
        for (JniLib.JniPerson p : ps) { p.close(); }
        // A ref Vec of handles comes back as views; a scalar Vec field and a
        // callback taking and returning a scalar Vec copy.
        try (JniLib.JniTeam team = JniLib.jni_team(new String[] { "p", "q" })) {
            JniLib.JniPerson[] views = JniLib.jni_team_people(team);
            views[1].age(99);
            System.out.println(JniLib.jni_oldest(JniLib.jni_team_people(team)) + " "
                + Arrays.toString(team.scores()));
            team.scores(new long[] { 4, 5, 6 });
            System.out.println(Arrays.toString(team.scores()));
        }
        System.out.println(JniLib.jni_map_sum(v -> { long[] w = new long[v.length + 1]; for (int i = 0; i < v.length; i++) { w[i] = v[i] * 10; } w[v.length] = 1; return w; }));
        for (int i = 0; i < 100000; i++) {
            check(JniLib.jni_sum(JniLib.jni_range(4)) == 14, "vec loop");
            JniLib.JniPerson[] loop = JniLib.jni_people(new String[] { "x", "y" });
            check(JniLib.jni_oldest(loop).equals("y") && JniLib.jni_adopt(loop) == 2, "handle vec loop");
            for (JniLib.JniPerson p : loop) { p.close(); }
        }
        // Callbacks that throw, write mut parameters back, and take own ones.
        System.out.println(JniLib.jni_try(x -> x * 2, 21));
        System.out.println(JniLib.jni_try(x -> { throw new JniLib.TilError("JniErr", "neg " + x); }, -1));
        System.out.println(JniLib.jni_try(x -> { throw new JniLib.TilError("DivideByZero"); }, 0));
        System.out.println(JniLib.jni_try(x -> { throw new JniLib.TilError("JniBad"); }, 0));
        System.out.println(JniLib.jni_mut_cb((k, s, b, xs, ss) -> {
            k[0] += 41;
            s[0] = s[0] + "bc";
            b[0] = !b[0];
            long[] w = Arrays.copyOf(xs[0], xs[0].length + 1);
            w[w.length - 1] = 9;
            xs[0] = w;
            ss[0] = new String[] { ss[0][0], "q" };
        }));
        System.out.println(JniLib.jni_mut_person(p -> { p.age(p.age() + 10); p.name("mm"); }));
        JniLib.JniPerson[] kept = new JniLib.JniPerson[1];
        System.out.println(JniLib.jni_own_cb((s, p, xs) -> { kept[0] = p; return s.length() * 100 + xs[0]; }));
        System.out.println(kept[0].name() + " " + kept[0].age());
        kept[0].close();
        for (int i = 0; i < 100000; i++) {
            check(JniLib.jni_try(x -> { throw new JniLib.TilError("JniErr", "e"); }, i).equals("JniErr e 7"),
                "throw callback loop");
            check(JniLib.jni_own_cb((s, p, xs) -> { p.close(); return 1; }) == 1, "own callback loop");
            check(JniLib.jni_mut_cb((k, s, b, xs, ss) -> { s[0] = "z"; ss[0] = new String[0]; }).startsWith("1 z"),
                "mut callback loop");
        }
        // Vecs of handles into and out of a callback: borrowed views, owned
        // handles (one returned, one closed), and a returned array moved into til.
        System.out.println(JniLib.jni_people_cb((xs, ys) -> {
            JniLib.JniPerson made = new JniLib.JniPerson();
            made.name("z");
            made.age(xs[1].age() + 7);
            ys[1].close();
            return new JniLib.JniPerson[] { made, ys[0] };
        }));
        for (int i = 0; i < 100000; i++) {
            check(JniLib.jni_people_cb((xs, ys) -> { ys[1].close(); return new JniLib.JniPerson[] { ys[0] }; })
                .equals("1 c b"), "handle vec callback loop");
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
