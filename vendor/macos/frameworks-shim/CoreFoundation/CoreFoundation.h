/* SDK-less shim for <CoreFoundation/CoreFoundation.h> (issue #25 / #232).
 *
 * Only the CoreFoundation surface raylib's RGFW backend + minigamepad
 * touch. Objects are opaque pointers; the functions and the few data
 * symbols (kCFRunLoopDefaultMode, the CFType dictionary callbacks, the
 * CFSTR constant-string class) bind at runtime on a real mac via the
 * CoreFoundation .tbd stub. Values/typedefs are the documented ABI.
 */
#ifndef _TIL_SHIM_COREFOUNDATION_H
#define _TIL_SHIM_COREFOUNDATION_H

#include <stdint.h>
#include <stddef.h>
/* Apple availability macros (API_AVAILABLE / API_DEPRECATED / ...). raylib's
 * RGFW backend uses them in enum declarations but never includes a header
 * that pulls them (it drives Cocoa via the objc runtime), so define them
 * here -- the vendored os/availability.h is the real Apple one. */
#include <os/availability.h>

typedef unsigned char        Boolean;
typedef unsigned char        UInt8;
typedef signed   int         SInt32;
typedef unsigned int         UInt32;
typedef signed   long        CFIndex;
typedef unsigned long        CFTypeID;
typedef unsigned long        CFOptionFlags;
typedef unsigned long        CFHashCode;
typedef double               CFTimeInterval;
typedef uint32_t             CFStringEncoding;

typedef const void *         CFTypeRef;
typedef const struct __CFString     *CFStringRef;
typedef struct __CFString           *CFMutableStringRef;
typedef const struct __CFAllocator  *CFAllocatorRef;
typedef const struct __CFArray      *CFArrayRef;
typedef struct __CFArray            *CFMutableArrayRef;
typedef const struct __CFDictionary *CFDictionaryRef;
typedef struct __CFDictionary       *CFMutableDictionaryRef;
typedef const struct __CFNumber     *CFNumberRef;
typedef const struct __CFData       *CFDataRef;
typedef struct __CFBundle           *CFBundleRef;
typedef const struct __CFURL        *CFURLRef;
typedef struct __CFRunLoop          *CFRunLoopRef;
typedef CFStringRef                  CFRunLoopMode;

typedef CFIndex CFComparisonResult;
enum { kCFCompareLessThan = -1, kCFCompareEqualTo = 0, kCFCompareGreaterThan = 1 };

typedef CFIndex CFNumberType;
enum {
    kCFNumberSInt8Type = 1, kCFNumberSInt16Type = 2, kCFNumberSInt32Type = 3,
    kCFNumberSInt64Type = 4, kCFNumberFloat32Type = 5, kCFNumberFloat64Type = 6,
    kCFNumberCharType = 7, kCFNumberShortType = 8, kCFNumberIntType = 9,
    kCFNumberLongType = 10, kCFNumberLongLongType = 11, kCFNumberFloatType = 12,
    kCFNumberDoubleType = 13, kCFNumberCFIndexType = 14
};

enum { kCFStringEncodingASCII = 0x0600, kCFStringEncodingUTF8 = 0x08000100 };

/* kCFAllocatorDefault is a documented synonym for NULL (the default
 * allocator), so no runtime symbol is needed. */
#define kCFAllocatorDefault ((CFAllocatorRef)0)

/* Dictionary callback descriptor structs. We only ever take the address of
 * the two kCFType* externs (resolved to real CoreFoundation data at
 * runtime), so the layout just needs to be a valid complete type. */
typedef struct {
    CFIndex version; void *retain; void *release;
    void *copyDescription; void *equal; void *hash;
} CFDictionaryKeyCallBacks;
typedef struct {
    CFIndex version; void *retain; void *release;
    void *copyDescription; void *equal;
} CFDictionaryValueCallBacks;

extern const CFDictionaryKeyCallBacks   kCFTypeDictionaryKeyCallBacks;
extern const CFDictionaryValueCallBacks kCFTypeDictionaryValueCallBacks;
extern const CFStringRef                kCFRunLoopDefaultMode;

/* Constant CFString literal -- clang lowers this to a __CFConstantString
 * that references ___CFConstantStringClassReference (CoreFoundation .tbd). */
#define CFSTR(cStr) ((CFStringRef)__builtin___CFStringMakeConstantString("" cStr ""))

void       CFRelease(CFTypeRef cf);
CFTypeRef  CFRetain(CFTypeRef cf);
CFTypeID   CFGetTypeID(CFTypeRef cf);

CFIndex     CFArrayGetCount(CFArrayRef theArray);
const void *CFArrayGetValueAtIndex(CFArrayRef theArray, CFIndex idx);

CFMutableDictionaryRef CFDictionaryCreateMutable(CFAllocatorRef allocator,
    CFIndex capacity, const CFDictionaryKeyCallBacks *keyCallBacks,
    const CFDictionaryValueCallBacks *valueCallBacks);
void CFDictionarySetValue(CFMutableDictionaryRef theDict,
    const void *key, const void *value);

CFNumberRef CFNumberCreate(CFAllocatorRef allocator, CFNumberType theType, const void *valuePtr);
Boolean     CFNumberGetValue(CFNumberRef number, CFNumberType theType, void *valuePtr);

CFStringRef CFStringCreateWithCString(CFAllocatorRef alloc, const char *cStr, CFStringEncoding encoding);
Boolean     CFStringGetCString(CFStringRef theString, char *buffer, CFIndex bufferSize, CFStringEncoding encoding);
CFComparisonResult CFStringCompare(CFStringRef theString1, CFStringRef theString2, CFOptionFlags compareOptions);

CFRunLoopRef CFRunLoopGetCurrent(void);
SInt32       CFRunLoopRunInMode(CFRunLoopMode mode, CFTimeInterval seconds, Boolean returnAfterSourceHandled);

CFBundleRef CFBundleGetMainBundle(void);
CFBundleRef CFBundleGetBundleWithIdentifier(CFStringRef bundleID);
CFURLRef    CFBundleCopyResourcesDirectoryURL(CFBundleRef bundle);
void       *CFBundleGetDataPointerForName(CFBundleRef bundle, CFStringRef symbolName);
void       *CFBundleGetFunctionPointerForName(CFBundleRef bundle, CFStringRef functionName);

const UInt8 *CFDataGetBytePtr(CFDataRef theData);
CFStringRef  CFURLCopyLastPathComponent(CFURLRef url);
Boolean      CFURLGetFileSystemRepresentation(CFURLRef url, Boolean resolveAgainstBase, UInt8 *buffer, CFIndex maxBufLen);

#endif /* _TIL_SHIM_COREFOUNDATION_H */
