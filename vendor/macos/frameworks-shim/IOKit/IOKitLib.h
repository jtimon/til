/* SDK-less shim for <IOKit/IOKitLib.h> (issue #25 / #232).
 * IOKit base types + the service/registry calls minigamepad uses. The
 * functions bind at runtime via the IOKit .tbd stub. */
#ifndef _TIL_SHIM_IOKITLIB_H
#define _TIL_SHIM_IOKITLIB_H

#include <stdint.h>
#include <CoreFoundation/CoreFoundation.h>

typedef int          kern_return_t;
typedef unsigned int mach_port_t;
typedef mach_port_t  io_object_t;
typedef io_object_t  io_service_t;
typedef io_object_t  io_iterator_t;
typedef io_object_t  io_registry_entry_t;
typedef io_object_t  io_connect_t;
typedef kern_return_t IOReturn;
typedef uint32_t     IOOptionBits;

/* MACH_PORT_NULL; the default main/master IOKit port. */
#define kIOMainPortDefault   ((mach_port_t)0)
#define kIOMasterPortDefault ((mach_port_t)0)

#define kIOReturnSuccess 0

CFMutableDictionaryRef IOServiceMatching(const char *name);
kern_return_t IOServiceGetMatchingServices(mach_port_t mainPort, CFDictionaryRef matching, io_iterator_t *existing);
io_object_t   IOIteratorNext(io_iterator_t iterator);
kern_return_t IOObjectRelease(io_object_t object);
CFTypeRef     IORegistryEntryCreateCFProperty(io_registry_entry_t entry, CFStringRef key, CFAllocatorRef allocator, IOOptionBits options);

#endif /* _TIL_SHIM_IOKITLIB_H */
