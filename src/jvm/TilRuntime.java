package til.runtime;

import java.nio.charset.StandardCharsets;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Locale;
import java.util.Map;
import java.util.WeakHashMap;

public final class TilRuntime {
    private TilRuntime() {}

    private static final int CAP_LITERAL = -1;
    private static final int CAP_VIEW = -2;

    public static final class Str {
        private Ptr data;
        private int count;
        private int capacity;
        private boolean deleted;

        private Str(byte[] bytes, boolean literal) {
            data = malloc(bytes.length);
            System.arraycopy(bytes, 0, data.block.bytes, 0, bytes.length);
            count = bytes.length;
            capacity = literal ? CAP_LITERAL : bytes.length;
        }

        private Str(Ptr data, int count, int capacity) {
            this.data = data;
            this.count = count;
            this.capacity = capacity;
        }

        private byte[] bytes() {
            if (deleted) { throw new IllegalStateException("use after Str.delete"); }
            checkedRange(data, count);
            return Arrays.copyOfRange(data.block.bytes, data.offset, data.offset + count);
        }

        public Ptr get_p_c_x5fstr() { return data; }
        public void set_p_c_x5fstr(Ptr value) { data = value; }
        public int get_p_count() { return count; }
        public void set_p_count(int value) { count = value; }
        public int get_p_cap() { return capacity; }
        public void set_p_cap(int value) { capacity = value; }
    }

    public interface I8Slot { byte getI8(); void setI8(byte value); }
    public interface U8Slot { int getU8(); void setU8(int value); }
    public interface I16Slot { short getI16(); void setI16(short value); }
    public interface U16Slot { int getU16(); void setU16(int value); }
    public interface I32Slot { int getI32(); void setI32(int value); }
    public interface U32Slot { int getU32(); void setU32(int value); }
    public interface I64Slot { long getI64(); void setI64(long value); }
    public interface U64Slot { long getU64(); void setU64(long value); }
    public interface F32Slot { float getF32(); void setF32(float value); }
    public interface F64Slot { double getF64(); void setF64(double value); }
    public interface BoolSlot { boolean getBool(); void setBool(boolean value); }
    public interface StrParts { int length(); Str part(int index); }
    public interface Closure {}
    public interface EnumValue {
        long tilTag();
        Object tilPayload();
        String tilVariantName();
    }

    private static final class ClosureState {
        private int references = 1;
        private boolean deleted;
    }

    private static final Map<Closure, ClosureState> CLOSURES = new WeakHashMap<>();

    private static ClosureState closureState(Closure closure) {
        return CLOSURES.computeIfAbsent(closure, ignored -> new ClosureState());
    }

    public static void checkClosure(Closure closure) {
        if (closureState(closure).deleted) {
            throw new IllegalStateException("call through deleted closure");
        }
    }

    public static <T extends Closure> T retainClosure(T closure) {
        ClosureState state = closureState(closure);
        if (state.deleted) { throw new IllegalStateException("retain of deleted closure"); }
        state.references++;
        return closure;
    }

    public static void releaseClosure(Closure closure) {
        ClosureState state = closureState(closure);
        if (state.deleted) { throw new IllegalStateException("double closure release"); }
        state.references--;
        if (state.references == 0) { state.deleted = true; }
    }

    public static boolean enumIs(Object value, long tag) {
        return ((EnumValue) value).tilTag() == tag;
    }

    public static boolean enumIs(Object value, Object other) {
        return ((EnumValue) value).tilTag() == ((EnumValue) other).tilTag();
    }

    public static Object enumPayload(Object value) {
        return ((EnumValue) value).tilPayload();
    }

    public static Str dynTypeToStr(EnumValue type) {
        String variant = type.tilVariantName();
        Object payload = type.tilPayload();
        if (variant.equals("Primitive")) {
            variant = ((EnumValue) payload).tilVariantName();
        } else if (variant.equals("Struct") || variant.equals("Enum")
                || variant.equals("Custom") || variant.equals("FuncPtrSig")) {
            return cloneStr((Str) payload);
        } else if (variant.equals("FuncPtr") || variant.equals("FuncDef")) {
            variant = "Fn";
        }
        return hostStr(variant);
    }

    public static final class I8Cell implements I8Slot {
        public byte value;
        public I8Cell(byte value) { this.value = value; }
        public byte getI8() { return value; }
        public void setI8(byte value) { this.value = value; }
    }
    public static final class U8Cell implements U8Slot {
        public int value;
        public U8Cell(int value) { this.value = value & 0xff; }
        public int getU8() { return value; }
        public void setU8(int value) { this.value = value & 0xff; }
    }
    public static final class I16Cell implements I16Slot {
        public short value;
        public I16Cell(short value) { this.value = value; }
        public short getI16() { return value; }
        public void setI16(short value) { this.value = value; }
    }
    public static final class U16Cell implements U16Slot {
        public int value;
        public U16Cell(int value) { this.value = value & 0xffff; }
        public int getU16() { return value; }
        public void setU16(int value) { this.value = value & 0xffff; }
    }
    public static final class I32Cell implements I32Slot {
        public int value;
        public I32Cell(int value) { this.value = value; }
        public int getI32() { return value; }
        public void setI32(int value) { this.value = value; }
    }
    public static final class U32Cell implements U32Slot {
        public int value;
        public U32Cell(int value) { this.value = value; }
        public int getU32() { return value; }
        public void setU32(int value) { this.value = value; }
    }
    public static final class I64Cell implements I64Slot {
        public long value;
        public I64Cell(long value) { this.value = value; }
        public long getI64() { return value; }
        public void setI64(long value) { this.value = value; }
    }
    public static final class U64Cell implements U64Slot {
        public long value;
        public U64Cell(long value) { this.value = value; }
        public long getU64() { return value; }
        public void setU64(long value) { this.value = value; }
    }
    public static final class F32Cell implements F32Slot {
        public float value;
        public F32Cell(float value) { this.value = value; }
        public float getF32() { return value; }
        public void setF32(float value) { this.value = value; }
    }
    public static final class F64Cell implements F64Slot {
        public double value;
        public F64Cell(double value) { this.value = value; }
        public double getF64() { return value; }
        public void setF64(double value) { this.value = value; }
    }
    public static final class BoolCell implements BoolSlot {
        public boolean value;
        public BoolCell(boolean value) { this.value = value; }
        public boolean getBool() { return value; }
        public void setBool(boolean value) { this.value = value; }
    }

    private static final class Block {
        private byte[] bytes;
        private final Map<Integer, ObjectSlot> objects = new HashMap<>();
        private boolean freed;

        private Block(int size) {
            bytes = new byte[size];
        }
    }

    private static final class ObjectSlot {
        private final int size;
        private final Object value;

        private ObjectSlot(int size, Object value) {
            this.size = size;
            this.value = value;
        }
    }

    public static final class Ptr implements I8Slot, U8Slot, I16Slot, U16Slot,
            I32Slot, U32Slot, I64Slot, U64Slot, F32Slot, F64Slot, BoolSlot {
        private final Block block;
        private final int offset;

        private Ptr(Block block, int offset) {
            this.block = block;
            this.offset = offset;
        }

        public byte getI8() { return loadI8(this); }
        public void setI8(byte value) { storeI8(this, value); }
        public int getU8() { return loadU8(this); }
        public void setU8(int value) { storeU8(this, value); }
        public short getI16() { return loadI16(this); }
        public void setI16(short value) { storeI16(this, value); }
        public int getU16() { return loadU16(this); }
        public void setU16(int value) { storeU16(this, value); }
        public int getI32() { return loadI32(this); }
        public void setI32(int value) { storeI32(this, value); }
        public int getU32() { return loadU32(this); }
        public void setU32(int value) { storeU32(this, value); }
        public long getI64() { return loadI64(this); }
        public void setI64(long value) { storeI64(this, value); }
        public long getU64() { return loadU64(this); }
        public void setU64(long value) { storeU64(this, value); }
        public float getF32() { return loadF32(this); }
        public void setF32(float value) { storeF32(this, value); }
        public double getF64() { return loadF64(this); }
        public void setF64(double value) { storeF64(this, value); }
        public boolean getBool() { return loadBool(this); }
        public void setBool(boolean value) { storeBool(this, value); }
    }

    private static Block liveBlock(Ptr ptr) {
        if (ptr == null) { throw new IllegalStateException("null pointer"); }
        if (ptr.block.freed) { throw new IllegalStateException("use after free"); }
        return ptr.block;
    }

    private static int checkedSize(long value) {
        if (value < 0 || value > Integer.MAX_VALUE) {
            throw new ArithmeticException("JVM allocation exceeds signed 32-bit storage");
        }
        return (int) value;
    }

    private static int checkedRange(Ptr ptr, long length) {
        Block block = liveBlock(ptr);
        int count = checkedSize(length);
        if (ptr.offset < 0 || ptr.offset > block.bytes.length - count) {
            throw new IndexOutOfBoundsException("virtual heap access out of bounds");
        }
        return count;
    }

    private static void rejectObjectOverlap(Block block, int offset, int length) {
        int end = offset + length;
        for (Map.Entry<Integer, ObjectSlot> entry : block.objects.entrySet()) {
            int objectOffset = entry.getKey();
            int objectEnd = objectOffset + entry.getValue().size;
            if (objectOffset < end && objectEnd > offset) {
                throw new IllegalStateException("byte write overlaps typed object slot");
            }
        }
    }

    public static Ptr malloc(long count) {
        return new Ptr(new Block(checkedSize(count)), 0);
    }

    public static Ptr calloc(long count, long size) {
        return malloc(Math.multiplyExact(count, size));
    }

    public static Ptr realloc(Ptr ptr, long count) {
        if (ptr == null) { return malloc(count); }
        Block old = liveBlock(ptr);
        if (ptr.offset != 0) { throw new IllegalStateException("realloc of interior pointer"); }
        Block replacement = new Block(checkedSize(count));
        System.arraycopy(old.bytes, 0, replacement.bytes, 0,
            Math.min(old.bytes.length, replacement.bytes.length));
        for (Map.Entry<Integer, ObjectSlot> entry : old.objects.entrySet()) {
            if (entry.getKey() + entry.getValue().size <= replacement.bytes.length) {
                replacement.objects.put(entry.getKey(), entry.getValue());
            }
        }
        old.freed = true;
        return new Ptr(replacement, 0);
    }

    public static Ptr cloneBlock(Ptr ptr) {
        Block source = liveBlock(ptr);
        int length = source.bytes.length - ptr.offset;
        Block copy = new Block(length);
        System.arraycopy(source.bytes, ptr.offset, copy.bytes, 0, length);
        for (Map.Entry<Integer, ObjectSlot> entry : source.objects.entrySet()) {
            int relative = entry.getKey() - ptr.offset;
            if (relative >= 0 && relative + entry.getValue().size <= length) {
                copy.objects.put(relative, entry.getValue());
            }
        }
        return new Ptr(copy, 0);
    }

    public static Ptr precomputedValues(int capacity, int elementSize, Object... values) {
        Ptr data = calloc(capacity, elementSize);
        for (int i = 0; i < values.length; i++) {
            Ptr slot = ptrAdd(data, (long) i * elementSize);
            Object value = values[i];
            if (value instanceof Float f) {
                storeUnsigned(slot, Float.floatToRawIntBits(f), elementSize);
            } else if (value instanceof Double d) {
                storeUnsigned(slot, Double.doubleToRawLongBits(d), elementSize);
            } else if (value instanceof Number n) {
                storeUnsigned(slot, n.longValue(), elementSize);
            } else if (value instanceof Boolean b) {
                storeUnsigned(slot, b ? 1 : 0, elementSize);
            } else {
                storeObject(slot, value, elementSize);
            }
        }
        return data;
    }

    public static void free(Ptr ptr) {
        if (ptr == null) { throw new IllegalStateException("null pointer"); }
        if (ptr.block.freed) { throw new IllegalStateException("double free"); }
        Block block = ptr.block;
        if (ptr.offset != 0) { throw new IllegalStateException("free of interior pointer"); }
        block.freed = true;
        block.objects.clear();
    }

    public static void releaseBox(Object value) {
        if (value instanceof Ptr ptr) { free(ptr); }
    }

    // Scalar delete has no payload destructor; Java GC owns any wrapper cell.
    public static void dropScalar() {}

    public static Ptr ptrAdd(Ptr ptr, long offset) {
        Block block = liveBlock(ptr);
        long next = (long) ptr.offset + offset;
        if (next < 0 || next > block.bytes.length) {
            throw new IndexOutOfBoundsException("virtual heap pointer addition out of bounds");
        }
        return new Ptr(block, (int) next);
    }

    public static boolean ptrEq(Ptr left, Ptr right) {
        return left == right || left != null && right != null
            && left.block == right.block && left.offset == right.offset;
    }

    public static void memcpy(Ptr dest, Ptr src, long length) {
        int count = checkedRange(dest, length);
        checkedRange(src, length);
        int srcEnd = src.offset + count;
        int destEnd = dest.offset + count;
        Map<Integer, ObjectSlot> copiedObjects = new HashMap<>();
        for (Map.Entry<Integer, ObjectSlot> entry : src.block.objects.entrySet()) {
            int start = entry.getKey();
            int end = start + entry.getValue().size;
            if (start < srcEnd && end > src.offset) {
                if (start < src.offset || end > srcEnd) {
                    throw new IllegalStateException("partial read of typed object slot");
                }
                copiedObjects.put(dest.offset + start - src.offset, entry.getValue());
            }
        }
        Map<Integer, ObjectSlot> oldDestObjects = new HashMap<>(dest.block.objects);
        for (Map.Entry<Integer, ObjectSlot> entry : oldDestObjects.entrySet()) {
            int start = entry.getKey();
            int end = start + entry.getValue().size;
            if (start < destEnd && end > dest.offset) {
                if (start < dest.offset || end > destEnd) {
                    throw new IllegalStateException("partial write of typed object slot");
                }
                dest.block.objects.remove(start);
            }
        }
        System.arraycopy(src.block.bytes, src.offset, dest.block.bytes, dest.offset, count);
        dest.block.objects.putAll(copiedObjects);
    }

    public static void memcpy(Ptr dest, long value, long length) {
        int count = checkedRange(dest, length);
        if (count > Long.BYTES) { throw new IllegalArgumentException("scalar memcpy exceeds scalar width"); }
        rejectObjectOverlap(dest.block, dest.offset, count);
        for (int i = 0; i < count; i++) {
            dest.block.bytes[dest.offset + i] = (byte) (value >>> (i * 8));
        }
    }

    public static void memcpy(Ptr dest, Object value, long length) {
        storeObject(dest, value, length);
    }

    public static void memmove(Ptr dest, Ptr src, long length) {
        memcpy(dest, src, length);
    }

    public static void memset(Ptr dest, int value, long length) {
        int count = checkedRange(dest, length);
        rejectObjectOverlap(dest.block, dest.offset, count);
        Arrays.fill(dest.block.bytes, dest.offset, dest.offset + count, (byte) value);
    }

    public static int memcmp(Ptr left, Ptr right, long length) {
        int count = checkedRange(left, length);
        checkedRange(right, length);
        for (int i = 0; i < count; i++) {
            int a = left.block.bytes[left.offset + i] & 0xff;
            int b = right.block.bytes[right.offset + i] & 0xff;
            if (a != b) { return Integer.compare(a, b); }
        }
        return 0;
    }

    private static long loadUnsigned(Ptr ptr, int width) {
        checkedRange(ptr, width);
        long value = 0;
        for (int i = 0; i < width; i++) {
            value |= (long) (ptr.block.bytes[ptr.offset + i] & 0xff) << (i * 8);
        }
        return value;
    }

    private static void storeUnsigned(Ptr ptr, long value, int width) {
        checkedRange(ptr, width);
        rejectObjectOverlap(ptr.block, ptr.offset, width);
        for (int i = 0; i < width; i++) {
            ptr.block.bytes[ptr.offset + i] = (byte) (value >>> (i * 8));
        }
    }

    public static byte loadI8(Ptr ptr) { return (byte) loadUnsigned(ptr, 1); }
    public static int loadU8(Ptr ptr) { return (int) loadUnsigned(ptr, 1); }
    public static short loadI16(Ptr ptr) { return (short) loadUnsigned(ptr, 2); }
    public static int loadU16(Ptr ptr) { return (int) loadUnsigned(ptr, 2); }
    public static int loadI32(Ptr ptr) { return (int) loadUnsigned(ptr, 4); }
    public static int loadU32(Ptr ptr) { return (int) loadUnsigned(ptr, 4); }
    public static long loadI64(Ptr ptr) { return loadUnsigned(ptr, 8); }
    public static long loadU64(Ptr ptr) { return loadUnsigned(ptr, 8); }
    public static float loadF32(Ptr ptr) { return Float.intBitsToFloat(loadI32(ptr)); }
    public static double loadF64(Ptr ptr) { return Double.longBitsToDouble(loadI64(ptr)); }
    public static boolean loadBool(Ptr ptr) { return loadU8(ptr) != 0; }

    public static void storeI8(Ptr ptr, byte value) { storeUnsigned(ptr, value, 1); }
    public static void storeU8(Ptr ptr, int value) { storeUnsigned(ptr, value, 1); }
    public static void storeI16(Ptr ptr, short value) { storeUnsigned(ptr, value, 2); }
    public static void storeU16(Ptr ptr, int value) { storeUnsigned(ptr, value, 2); }
    public static void storeI32(Ptr ptr, int value) { storeUnsigned(ptr, value, 4); }
    public static void storeU32(Ptr ptr, int value) { storeUnsigned(ptr, value, 4); }
    public static void storeI64(Ptr ptr, long value) { storeUnsigned(ptr, value, 8); }
    public static void storeU64(Ptr ptr, long value) { storeUnsigned(ptr, value, 8); }
    public static void storeF32(Ptr ptr, float value) { storeI32(ptr, Float.floatToRawIntBits(value)); }
    public static void storeF64(Ptr ptr, double value) { storeI64(ptr, Double.doubleToRawLongBits(value)); }
    public static void storeBool(Ptr ptr, boolean value) { storeU8(ptr, value ? 1 : 0); }

    public static Object loadObject(Ptr ptr, long size) {
        int width = checkedRange(ptr, size);
        ObjectSlot slot = ptr.block.objects.get(ptr.offset);
        if (slot == null) {
            throw new IllegalStateException("uninitialized typed object slot");
        }
        if (slot.size != width) { throw new IllegalStateException("typed object slot size mismatch"); }
        return slot.value;
    }

    public static Object value(Object carrier, long size) {
        if (carrier instanceof Ptr ptr) { return loadObject(ptr, size); }
        return carrier;
    }

    public static void storeObject(Ptr ptr, Object value, long size) {
        int width = checkedRange(ptr, size);
        ObjectSlot existing = ptr.block.objects.get(ptr.offset);
        if (existing != null && existing.size == width) {
            ptr.block.objects.remove(ptr.offset);
        }
        rejectObjectOverlap(ptr.block, ptr.offset, width);
        ptr.block.objects.put(ptr.offset, new ObjectSlot(width, value));
    }

    public static Ptr boxObject(Object value, long size) {
        Ptr ptr = malloc(size);
        storeObject(ptr, value, size);
        return ptr;
    }

    public static Ptr loadPtr(Ptr ptr) {
        return (Ptr) loadObject(ptr, Long.BYTES);
    }

    public static void storePtr(Ptr ptr, Ptr value) {
        storeObject(ptr, value, Long.BYTES);
    }

    public static Str str(byte[] bytes) {
        return new Str(bytes, false);
    }

    public static Str literalStr(byte[] bytes) {
        return new Str(bytes, true);
    }

    public static Str makeStr(Ptr data, int count, int capacity) {
        return new Str(data, count, capacity);
    }

    private static Str hostStr(String value) {
        return str(value.getBytes(StandardCharsets.UTF_8));
    }

    private static String general(double value, int precision) {
        if (Double.isNaN(value)) { return "nan"; }
        if (value == Double.POSITIVE_INFINITY) { return "inf"; }
        if (value == Double.NEGATIVE_INFINITY) { return "-inf"; }
        String raw = String.format(Locale.ROOT, "%." + precision + "g", value);
        int exponent = raw.indexOf('e');
        String suffix = exponent >= 0 ? raw.substring(exponent) : "";
        String mantissa = exponent >= 0 ? raw.substring(0, exponent) : raw;
        if (mantissa.indexOf('.') >= 0) {
            int end = mantissa.length();
            while (end > 0 && mantissa.charAt(end - 1) == '0') { end--; }
            if (end > 0 && mantissa.charAt(end - 1) == '.') { end--; }
            mantissa = mantissa.substring(0, end);
        }
        return mantissa + suffix;
    }

    private static int checkedIndex(long value) {
        if (value < 0 || value > Integer.MAX_VALUE) {
            throw new ArithmeticException("JVM array index exceeds signed 32-bit storage");
        }
        return (int) value;
    }

    public static Str[] newStrArray(int capacity) {
        return new Str[checkedIndex(Integer.toUnsignedLong(capacity))];
    }

    public static Str[] newStrArray(long capacity) {
        return new Str[checkedIndex(capacity)];
    }

    public static void setStr(Str[] values, int index, Str value) {
        values[checkedIndex(Integer.toUnsignedLong(index))] = value;
    }

    public static void setStr(Str[] values, long index, Str value) {
        values[checkedIndex(index)] = value;
    }

    public static boolean strEq(Str left, Str right) {
        return Arrays.equals(left.bytes(), right.bytes());
    }

    public static Str cloneStr(Str value) {
        return str(value.bytes());
    }

    public static Str cloneStrAt(Ptr ptr, long size) {
        checkedRange(ptr, size);
        ObjectSlot slot = ptr.block.objects.get(ptr.offset);
        if (slot == null) { return str(new byte[0]); }
        if (slot.size != size || !(slot.value instanceof Str value)) {
            throw new IllegalStateException("Str slot shape mismatch");
        }
        return cloneStr(value);
    }

    public static void deleteStr(Str value) {
        if (value.deleted) { throw new IllegalStateException("double Str.delete"); }
        if (Integer.compareUnsigned(value.capacity, CAP_VIEW) < 0) { free(value.data); }
        value.deleted = true;
    }

    public static void deleteStrAt(Ptr ptr, long size) {
        checkedRange(ptr, size);
        ObjectSlot slot = ptr.block.objects.get(ptr.offset);
        if (slot == null) { return; }
        if (slot.size != size || !(slot.value instanceof Str value)) {
            throw new IllegalStateException("Str slot shape mismatch");
        }
        deleteStr(value);
        ptr.block.objects.remove(ptr.offset);
    }

    public static void print(Str[] parts) {
        for (Str part : parts) {
            print_single(part);
        }
    }

    public static void print(StrParts parts) {
        for (int i = 0; i < parts.length(); i++) {
            print_single(parts.part(i));
        }
    }

    public static void println(Str[] parts) {
        print(parts);
        printFlush();
    }

    public static void println(StrParts parts) {
        print(parts);
        printFlush();
    }

    public static void eprint(Str[] parts) {
        for (Str part : parts) {
            eprint_single(part);
        }
    }

    public static void eprint(StrParts parts) {
        for (int i = 0; i < parts.length(); i++) {
            eprint_single(parts.part(i));
        }
    }

    public static void eprintln(Str[] parts) {
        eprint(parts);
        System.err.println();
    }

    public static void eprintln(StrParts parts) {
        eprint(parts);
        System.err.println();
    }

    public static void print_single(Str value) {
        byte[] bytes = value.bytes();
        System.out.write(bytes, 0, bytes.length);
    }

    public static void eprint_single(Str value) {
        byte[] bytes = value.bytes();
        System.err.write(bytes, 0, bytes.length);
    }

    public static void printFlush() {
        System.out.println();
    }

    public static void exit(int code) {
        System.exit(code);
    }

    public static void panic(StrParts parts, Str location) {
        eprint(parts);
        eprint_single(location);
        System.err.println();
        throw new IllegalStateException("til panic");
    }

    public static void assertTrue(boolean condition, Str location) {
        if (!condition) {
            eprint_single(location);
            System.err.println();
            throw new AssertionError("til assert failed");
        }
    }

    public static void expect(boolean condition, Str message, Str location) {
        if (!condition) {
            eprint_single(message);
            System.err.print(" at ");
            eprint_single(location);
            System.err.println();
            throw new AssertionError("til expect failed");
        }
    }

    public static void expect(boolean condition, StrParts message, Str location) {
        if (!condition) {
            eprint(message);
            System.err.print(" at ");
            eprint_single(location);
            System.err.println();
            throw new AssertionError("til expect failed");
        }
    }

    private static void assertionFailed(Str location) {
        eprint_single(location);
        System.err.println();
        throw new AssertionError("til assert_eq failed");
    }

    public static void assertEq(byte left, byte right, Str location) { if (left != right) { assertionFailed(location); } }
    public static void assertEq(short left, short right, Str location) { if (left != right) { assertionFailed(location); } }
    public static void assertEq(int left, int right, Str location) { if (left != right) { assertionFailed(location); } }
    public static void assertEq(long left, long right, Str location) { if (left != right) { assertionFailed(location); } }
    public static void assertEq(float left, float right, Str location) { if (left != right) { assertionFailed(location); } }
    public static void assertEq(double left, double right, Str location) { if (left != right) { assertionFailed(location); } }
    public static void assertEq(boolean left, boolean right, Str location) { if (left != right) { assertionFailed(location); } }
    public static void assertEq(Str left, Str right, Str location) { if (!strEq(left, right)) { assertionFailed(location); } }
    public static void assertEq(Object left, Object right, Str location) {
        if (!java.util.Objects.equals(left, right)) { assertionFailed(location); }
    }

    public static Str strI8(byte value) { return hostStr(Byte.toString(value)); }
    public static Str strU8(int value) { return hostStr(Integer.toString(value & 0xff)); }
    public static Str strI16(short value) { return hostStr(Short.toString(value)); }
    public static Str strU16(int value) { return hostStr(Integer.toString(value & 0xffff)); }
    public static Str strI32(int value) { return hostStr(Integer.toString(value)); }
    public static Str strU32(int value) { return hostStr(Integer.toUnsignedString(value)); }
    public static Str strI64(long value) { return hostStr(Long.toString(value)); }
    public static Str strU64(long value) { return hostStr(Long.toUnsignedString(value)); }
    public static Str strF32(float value) { return hostStr(general(value, 6)); }
    public static Str strF64(double value) { return hostStr(general(value, 6)); }
    public static Str strBool(boolean value) { return hostStr(Boolean.toString(value)); }
    public static Str reprF32(float value) { return hostStr(general(value, 9)); }
    public static Str reprF64(double value) { return hostStr(general(value, 17)); }

    public static long cmpI8(byte a, byte b) { return a > b ? 1 : a < b ? -1 : 0; }
    public static long cmpU8(int a, int b) { return Integer.compare(a & 0xff, b & 0xff); }
    public static long cmpI16(short a, short b) { return a > b ? 1 : a < b ? -1 : 0; }
    public static long cmpU16(int a, int b) { return Integer.compare(a & 0xffff, b & 0xffff); }
    public static long cmpI32(int a, int b) { return a > b ? 1 : a < b ? -1 : 0; }
    public static long cmpU32(int a, int b) { return Integer.compareUnsigned(a, b); }
    public static long cmpI64(long a, long b) { return a > b ? 1 : a < b ? -1 : 0; }
    public static long cmpU64(long a, long b) { return Long.compareUnsigned(a, b); }
    public static long cmpF32(float a, float b) { return a > b ? 1 : a < b ? -1 : 0; }
    public static long cmpF64(double a, double b) { return a > b ? 1 : a < b ? -1 : 0; }

    public static float u64ToF32(long value) { return (float) u64ToF64(value); }
    public static double u64ToF64(long value) {
        if (value >= 0) { return (double) value; }
        return (double) (value >>> 1) * 2.0 + (value & 1);
    }

    public static byte divI8(byte a, byte b) { return b == 0 ? 0 : (byte) (a / b); }
    public static int divU8(int a, int b) { return b == 0 ? 0 : (a & 0xff) / (b & 0xff); }
    public static short divI16(short a, short b) { return b == 0 ? 0 : (short) (a / b); }
    public static int divU16(int a, int b) { return b == 0 ? 0 : (a & 0xffff) / (b & 0xffff); }
    public static int divI32(int a, int b) { return b == 0 ? 0 : a / b; }
    public static int divU32(int a, int b) { return b == 0 ? 0 : Integer.divideUnsigned(a, b); }
    public static long divI64(long a, long b) { return b == 0 ? 0 : a / b; }
    public static long divU64(long a, long b) { return b == 0 ? 0 : Long.divideUnsigned(a, b); }
    public static float divF32(float a, float b) { return b == 0 ? 0 : a / b; }
    public static double divF64(double a, double b) { return b == 0 ? 0 : a / b; }

    public static byte modI8(byte a, byte b) { return b == 0 ? 0 : (byte) (a % b); }
    public static int modU8(int a, int b) { return b == 0 ? 0 : (a & 0xff) % (b & 0xff); }
    public static short modI16(short a, short b) { return b == 0 ? 0 : (short) (a % b); }
    public static int modU16(int a, int b) { return b == 0 ? 0 : (a & 0xffff) % (b & 0xffff); }
    public static int modI32(int a, int b) { return b == 0 ? 0 : a % b; }
    public static int modU32(int a, int b) { return b == 0 ? 0 : Integer.remainderUnsigned(a, b); }
    public static long modI64(long a, long b) { return b == 0 ? 0 : a % b; }
    public static long modU64(long a, long b) { return b == 0 ? 0 : Long.remainderUnsigned(a, b); }
    public static float modF32(float a, float b) { return b == 0 ? 0 : a % b; }
    public static double modF64(double a, double b) { return b == 0 ? 0 : a % b; }
}
