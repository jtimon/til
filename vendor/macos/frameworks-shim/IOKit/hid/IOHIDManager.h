/* SDK-less shim for <IOKit/hid/IOHIDManager.h> (issue #25 / #232).
 * The IOHID Manager/Device/Element/Value surface minigamepad uses for
 * gamepad support. Objects are opaque; functions bind at runtime via the
 * IOKit .tbd stub. The kIOHID*Key macros are the real string values. */
#ifndef _TIL_SHIM_IOHIDMANAGER_H
#define _TIL_SHIM_IOHIDMANAGER_H

#include <stdint.h>
#include <IOKit/IOKitLib.h>
#include <CoreFoundation/CoreFoundation.h>

typedef struct __IOHIDManager *IOHIDManagerRef;
typedef struct __IOHIDDevice  *IOHIDDeviceRef;
typedef struct __IOHIDElement *IOHIDElementRef;
typedef struct __IOHIDValue   *IOHIDValueRef;

typedef uint32_t IOHIDElementType;
enum {
    kIOHIDElementTypeInput_Misc   = 1,
    kIOHIDElementTypeInput_Button = 2,
    kIOHIDElementTypeInput_Axis   = 3,
    kIOHIDElementTypeInput_ScanCodes = 4
};

typedef uint32_t IOHIDOptionsType;
enum { kIOHIDOptionsTypeNone = 0 };

/* Device property keys -- plain C-string macros in the real header. */
#define kIOHIDVendorIDKey        "VendorID"
#define kIOHIDProductIDKey       "ProductID"
#define kIOHIDProductKey         "Product"
#define kIOHIDVersionNumberKey   "VersionNumber"
#define kIOHIDPrimaryUsageKey    "PrimaryUsage"
#define kIOHIDPrimaryUsagePageKey "PrimaryUsagePage"
#define kIOHIDDeviceUsagePageKey "DeviceUsagePage"
#define kIOHIDDeviceUsageKey     "DeviceUsage"

typedef void (*IOHIDDeviceCallback)(void *context, IOReturn result, void *sender, IOHIDDeviceRef device);
typedef void (*IOHIDValueCallback)(void *context, IOReturn result, void *sender, IOHIDValueRef value);

IOHIDManagerRef IOHIDManagerCreate(CFAllocatorRef allocator, IOOptionBits options);
void    IOHIDManagerSetDeviceMatching(IOHIDManagerRef manager, CFDictionaryRef matching);
void    IOHIDManagerRegisterDeviceMatchingCallback(IOHIDManagerRef manager, IOHIDDeviceCallback callback, void *context);
void    IOHIDManagerRegisterDeviceRemovalCallback(IOHIDManagerRef manager, IOHIDDeviceCallback callback, void *context);
void    IOHIDManagerScheduleWithRunLoop(IOHIDManagerRef manager, CFRunLoopRef runLoop, CFStringRef runLoopMode);
IOReturn IOHIDManagerOpen(IOHIDManagerRef manager, IOOptionBits options);

CFTypeRef  IOHIDDeviceGetProperty(IOHIDDeviceRef device, CFStringRef key);
CFArrayRef IOHIDDeviceCopyMatchingElements(IOHIDDeviceRef device, CFDictionaryRef matching, IOOptionBits options);
void       IOHIDDeviceRegisterInputValueCallback(IOHIDDeviceRef device, IOHIDValueCallback callback, void *context);

CFTypeID         IOHIDElementGetTypeID(void);
IOHIDElementType IOHIDElementGetType(IOHIDElementRef element);
uint32_t         IOHIDElementGetUsage(IOHIDElementRef element);
uint32_t         IOHIDElementGetUsagePage(IOHIDElementRef element);
CFIndex          IOHIDElementGetLogicalMin(IOHIDElementRef element);
CFIndex          IOHIDElementGetLogicalMax(IOHIDElementRef element);
IOHIDDeviceRef   IOHIDElementGetDevice(IOHIDElementRef element);

IOHIDElementRef  IOHIDValueGetElement(IOHIDValueRef value);
CFIndex          IOHIDValueGetIntegerValue(IOHIDValueRef value);

#endif /* _TIL_SHIM_IOHIDMANAGER_H */
