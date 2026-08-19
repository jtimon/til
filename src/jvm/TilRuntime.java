package til.runtime;

import java.nio.charset.StandardCharsets;
import java.util.Arrays;

public final class TilRuntime {
    private TilRuntime() {}

    public static final class Str {
        private final byte[] bytes;

        private Str(byte[] bytes) {
            this.bytes = bytes;
        }
    }

    public static Str str(byte[] bytes) {
        return new Str(bytes);
    }

    private static Str hostStr(String value) {
        return str(value.getBytes(StandardCharsets.UTF_8));
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
        return Arrays.equals(left.bytes, right.bytes);
    }

    public static void print(Str[] parts) {
        for (Str part : parts) {
            print_single(part);
        }
    }

    public static void println(Str[] parts) {
        print(parts);
        printFlush();
    }

    public static void eprint(Str[] parts) {
        for (Str part : parts) {
            eprint_single(part);
        }
    }

    public static void eprintln(Str[] parts) {
        eprint(parts);
        System.err.println();
    }

    public static void print_single(Str value) {
        System.out.write(value.bytes, 0, value.bytes.length);
    }

    public static void eprint_single(Str value) {
        System.err.write(value.bytes, 0, value.bytes.length);
    }

    public static void printFlush() {
        System.out.println();
    }

    public static void exit(int code) {
        System.exit(code);
    }

    public static Str strI8(byte value) { return hostStr(Byte.toString(value)); }
    public static Str strU8(int value) { return hostStr(Integer.toString(value & 0xff)); }
    public static Str strI16(short value) { return hostStr(Short.toString(value)); }
    public static Str strU16(int value) { return hostStr(Integer.toString(value & 0xffff)); }
    public static Str strI32(int value) { return hostStr(Integer.toString(value)); }
    public static Str strU32(int value) { return hostStr(Integer.toUnsignedString(value)); }
    public static Str strI64(long value) { return hostStr(Long.toString(value)); }
    public static Str strU64(long value) { return hostStr(Long.toUnsignedString(value)); }
    public static Str strF32(float value) { return hostStr(Float.toString(value)); }
    public static Str strF64(double value) { return hostStr(Double.toString(value)); }
    public static Str strBool(boolean value) { return hostStr(Boolean.toString(value)); }

    public static byte divI8(byte a, byte b) { return b == 0 ? 0 : (byte) (a / b); }
    public static int divU8(int a, int b) { return b == 0 ? 0 : (a & 0xff) / (b & 0xff); }
    public static short divI16(short a, short b) { return b == 0 ? 0 : (short) (a / b); }
    public static int divU16(int a, int b) { return b == 0 ? 0 : (a & 0xffff) / (b & 0xffff); }
    public static int divI32(int a, int b) { return b == 0 ? 0 : a / b; }
    public static int divU32(int a, int b) { return b == 0 ? 0 : Integer.divideUnsigned(a, b); }
    public static long divI64(long a, long b) { return b == 0 ? 0 : a / b; }
    public static long divU64(long a, long b) { return b == 0 ? 0 : Long.divideUnsigned(a, b); }
    public static float divF32(float a, float b) { return a / b; }
    public static double divF64(double a, double b) { return a / b; }

    public static byte modI8(byte a, byte b) { return b == 0 ? 0 : (byte) (a % b); }
    public static int modU8(int a, int b) { return b == 0 ? 0 : (a & 0xff) % (b & 0xff); }
    public static short modI16(short a, short b) { return b == 0 ? 0 : (short) (a % b); }
    public static int modU16(int a, int b) { return b == 0 ? 0 : (a & 0xffff) % (b & 0xffff); }
    public static int modI32(int a, int b) { return b == 0 ? 0 : a % b; }
    public static int modU32(int a, int b) { return b == 0 ? 0 : Integer.remainderUnsigned(a, b); }
    public static long modI64(long a, long b) { return b == 0 ? 0 : a % b; }
    public static long modU64(long a, long b) { return b == 0 ? 0 : Long.remainderUnsigned(a, b); }
    public static float modF32(float a, float b) { return a % b; }
    public static double modF64(double a, double b) { return a % b; }
}
