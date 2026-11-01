// JVM caller for the JNI binding of test/library_namespace_a.til, the
// library whose Python binding test/library_namespace.til checks; run by
// `bin/til run test/jni.til jvm`. It reads and writes the same globals the
// Python check does, then exercises struct handles.
import til.library_namespace_a.LibraryNamespaceA;
import til.library_namespace_a.LibraryNamespaceA.BindingNiche;
import til.library_namespace_a.LibraryNamespaceA.BindingPoint;
import til.library_namespace_a.LibraryNamespaceA.BindingTag;
import til.library_namespace_a.LibraryNamespaceA.BindingWidths;

public class LibraryNamespaceAJniTest {
    static void check(boolean ok, String what) {
        if (!ok) throw new AssertionError(what);
    }

    public static void main(String[] args) throws Exception {
        // The globals and namespace data the Python check reads and writes.
        check(LibraryNamespaceA.library_namespace_a_count() == 17, "count");
        check(LibraryNamespaceA.library_namespace_a_state() == 23, "state");
        check(LibraryNamespaceA.BindingPoint_COUNT() == 5, "BindingPoint.COUNT");
        check(LibraryNamespaceA.BindingPoint_STATE() == 6, "BindingPoint.STATE");
        check(LibraryNamespaceA.library_namespace_a_origin().scalar() == 19, "origin");
        check(LibraryNamespaceA.library_namespace_a_point_state().scalar() == 20, "point_state");
        check(LibraryNamespaceA.library_namespace_a_global_sum() == 51, "global_sum");
        LibraryNamespaceA.library_namespace_a_state(30);
        LibraryNamespaceA.BindingPoint_STATE(8);
        LibraryNamespaceA.library_namespace_a_point_state().scalar(24);
        check(LibraryNamespaceA.library_namespace_a_global_sum() == 60, "global_sum after writes");
        check(LibraryNamespaceA.library_namespace_a_point_state().scalar() == 24, "point_state after write");
        check(LibraryNamespaceA.library_namespace_a_origin_ref().scalar() == 19, "origin_ref.scalar");
        check(LibraryNamespaceA.library_namespace_a_origin_ref().size() == 29, "origin_ref.size");
        System.out.println("globals ok");

        // Enums: the tags the Python check reads, variant constructors and
        // payloads, and a niche enum's null variant.
        check(BindingTag.TAG_Empty == 3 && BindingTag.TAG_Number == 7, "BindingTag tags");
        try (BindingTag number = LibraryNamespaceA.BindingTag_Number(5);
             BindingTag empty = LibraryNamespaceA.BindingTag_Empty();
             BindingNiche none = LibraryNamespaceA.BindingNiche_None()) {
            check(number.tag() == BindingTag.TAG_Number && number.Number() == 5, "BindingTag.Number");
            check(empty.tag() == BindingTag.TAG_Empty, "BindingTag.Empty");
            check(none.tag() == BindingNiche.TAG_None, "BindingNiche.None");
        }
        System.out.println("enums ok");
        // A function alias, and a default constructor through a nested
        // constructor call.
        check(LibraryNamespaceA.library_namespace_a_value_alias() == 21, "value alias");
        try (LibraryNamespaceA.BindingNestedWidths n = new LibraryNamespaceA.BindingNestedWidths()) {
            check(n.prefix() == 17 && n.suffix() == 29, "nested defaults");
            check(n.inner().first() == 43 && n.inner().second() == 47 && n.inner().marker() == 53, "inner defaults");
        }

        // Owned struct handles: literal defaults, shallow in and out.
        try (BindingPoint p = new BindingPoint()) {
            check(p.scalar() == 7 && p.size() == 11 && p.ptr() == 13, "BindingPoint() defaults");
            p.scalar(91);
            try (BindingPoint q = LibraryNamespaceA.library_namespace_a_point(p)) {
                check(q.scalar() == 91 && q.size() == 11, "library_namespace_a_point");
            }
            try (BindingPoint r = LibraryNamespaceA.BindingPoint_identity(p)) {
                check(r.scalar() == 91, "BindingPoint_identity");
            }
        }
        // A mut struct parameter writes through to the caller's handle.
        try (BindingWidths a = new BindingWidths(); BindingWidths b = new BindingWidths()) {
            check(a.first() == 41 && a.second() == 73 && a.marker() == 123456789L, "BindingWidths() defaults");
            b.second(5);
            check(LibraryNamespaceA.library_widths_alias_read(a, b) == 5, "alias_read result");
            check(a.second() == 317, "alias_read wrote through mut");
        }
        // Borrowed handles view library storage; a write on either side shows on the other.
        LibraryNamespaceA.library_set_widths(77);
        check(LibraryNamespaceA.library_widths().second() == 77, "library_widths view");
        LibraryNamespaceA.library_widths().second(78);
        check(LibraryNamespaceA.library_widths_second() == 78, "library_widths write");
        // Str globals.
        check(LibraryNamespaceA.library_borrowed_text().equals("foreign text"), "text");
        LibraryNamespaceA.library_set_text();
        check(LibraryNamespaceA.library_borrowed_text().equals("changed abroad"), "text set abroad");
        LibraryNamespaceA.library_borrowed_text("set from java");
        check(LibraryNamespaceA.library_borrowed_text().equals("set from java"), "text set from java");
        // Scalars, Str arguments and throws.
        check(LibraryNamespaceA.library_namespace_a_default(31) == 31, "default");
        check(LibraryNamespaceA.library_namespace_a_string_default("a\"b\\c") == 5, "string_default");
        check(LibraryNamespaceA.library_namespace_a_core_string() == 5, "core_string");
        check(LibraryNamespaceA.library_namespace_a_throwing(4) == 4, "throwing ok");
        try {
            LibraryNamespaceA.library_namespace_a_throwing(-1);
            throw new AssertionError("library_namespace_a_throwing(-1) did not throw");
        } catch (LibraryNamespaceA.TilError e) {
            check(e.type().equals("BindingError"), "error type");
        }
        // A closed or borrowed handle fails loudly in Java.
        BindingPoint closed = new BindingPoint();
        closed.close();
        try {
            closed.scalar();
            throw new AssertionError("closed handle was usable");
        } catch (IllegalStateException e) {
            System.out.println("closed: " + e.getMessage());
        }
        // Many owned handles and Str round trips: nothing piles up.
        for (int i = 0; i < 100000; i++) {
            try (BindingPoint p = new BindingPoint(); BindingPoint q = LibraryNamespaceA.library_namespace_a_point(p)) {
                check(q.ptr() == 13, "loop point");
            }
            LibraryNamespaceA.library_borrowed_text("loop");
        }
        System.out.println("handles ok");
    }
}
