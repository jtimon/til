/* SDK-less shim for <Foundation/Foundation.h> (issue #25 / #232).
 * raylib's RGFW backend drives Cocoa entirely through the objc runtime
 * (objc_msgSend) and defines its own AppKit enum constants, so from
 * Foundation it only needs the scalar/geometry typedefs and the objc
 * runtime. Object handles are the runtime `id`. */
#ifndef _TIL_SHIM_FOUNDATION_H
#define _TIL_SHIM_FOUNDATION_H

#include <stdint.h>
#include <objc/objc.h>
#include <objc/runtime.h>
#include <objc/message.h>
#include <CoreGraphics/CoreGraphics.h>
#include <CoreFoundation/CoreFoundation.h>

typedef long          NSInteger;
typedef unsigned long NSUInteger;

typedef CGPoint NSPoint;
typedef CGSize  NSSize;
typedef CGRect  NSRect;
typedef struct { NSUInteger location, length; } NSRange;

#endif /* _TIL_SHIM_FOUNDATION_H */
