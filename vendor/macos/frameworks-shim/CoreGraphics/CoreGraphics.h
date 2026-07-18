/* SDK-less shim for <CoreGraphics/CoreGraphics.h> (issue #25 / #232).
 * Geometry types + the display/gamma/event calls raylib's RGFW backend
 * uses. Functions bind at runtime via the CoreGraphics .tbd stub. CGFloat
 * is 64-bit (double) on all supported (64-bit) mac targets. */
#ifndef _TIL_SHIM_COREGRAPHICS_H
#define _TIL_SHIM_COREGRAPHICS_H

#include <stdint.h>
#include <stddef.h>
#include <CoreFoundation/CoreFoundation.h>

typedef double CGFloat;
typedef struct { CGFloat x, y; }            CGPoint;
typedef struct { CGFloat width, height; }   CGSize;
typedef struct { CGPoint origin; CGSize size; } CGRect;

typedef uint32_t CGDirectDisplayID;
typedef uint32_t CGDisplayCount;
typedef struct CGDisplayMode *CGDisplayModeRef;
typedef float    CGGammaValue;
typedef struct __CGEvent       *CGEventRef;
typedef struct __CGEventSource *CGEventSourceRef;

typedef int32_t CGError;
enum { kCGErrorSuccess = 0 };

typedef int32_t CGWindowLevel;
typedef int32_t CGWindowLevelKey;
enum { kCGNormalWindowLevelKey = 4, kCGFloatingWindowLevelKey = 5 };
CGWindowLevel CGWindowLevelForKey(CGWindowLevelKey key);

/* Documented as the main display; evaluate it via CGMainDisplayID(). */
#define kCGDirectMainDisplay CGMainDisplayID()

CGDirectDisplayID CGMainDisplayID(void);
CGError CGGetActiveDisplayList(uint32_t maxDisplays, CGDirectDisplayID *activeDisplays, uint32_t *displayCount);
CGRect  CGDisplayBounds(CGDirectDisplayID display);
CGSize  CGDisplayScreenSize(CGDirectDisplayID display);
uint32_t CGDisplayUnitNumber(CGDirectDisplayID display);
CGDirectDisplayID CGOpenGLDisplayMaskToDisplayID(uint32_t mask);

CGDisplayModeRef CGDisplayCopyDisplayMode(CGDirectDisplayID display);
CFArrayRef       CGDisplayCopyAllDisplayModes(CGDirectDisplayID display, CFDictionaryRef options);
size_t           CGDisplayModeGetWidth(CGDisplayModeRef mode);
size_t           CGDisplayModeGetHeight(CGDisplayModeRef mode);
double           CGDisplayModeGetRefreshRate(CGDisplayModeRef mode);
CGError          CGDisplaySetDisplayMode(CGDirectDisplayID display, CGDisplayModeRef mode, CFDictionaryRef options);
void             CGDisplayModeRelease(CGDisplayModeRef mode);

CGError CGDisplayShowCursor(CGDirectDisplayID display);
CGError CGDisplayHideCursor(CGDirectDisplayID display);
CGError CGWarpMouseCursorPosition(CGPoint newCursorPosition);
CGError CGAssociateMouseAndMouseCursorPosition(int connected);

uint32_t CGDisplayGammaTableCapacity(CGDirectDisplayID display);
CGError  CGGetDisplayTransferByTable(CGDirectDisplayID display, uint32_t capacity,
             CGGammaValue *redTable, CGGammaValue *greenTable, CGGammaValue *blueTable, uint32_t *sampleCount);
CGError  CGSetDisplayTransferByTable(CGDirectDisplayID display, uint32_t capacity,
             const CGGammaValue *redTable, const CGGammaValue *greenTable, const CGGammaValue *blueTable);

CGEventRef CGEventCreate(CGEventSourceRef source);
CGPoint    CGEventGetLocation(CGEventRef event);

/* CGL pixel-format / renderer constants raylib's RGFW backend passes to
 * NSOpenGLPixelFormat (RGFW defines the NSOpenGLPFA* attribute IDs itself,
 * but not these two CGL values). Standard public CGL constants. */
#define kCGLRendererGenericFloatID              0x00020400
#define kCGLPFASupportsAutomaticGraphicsSwitching 101

#endif /* _TIL_SHIM_COREGRAPHICS_H */
