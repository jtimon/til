/* SDK-less shim for <CoreVideo/CoreVideo.h> (issue #25 / #232).
 * raylib's RGFW backend #includes this but references no CoreVideo symbol
 * on the desktop path; the opaque display-link types are provided in case
 * a transitive use appears. Real symbols (if any) bind via the CoreVideo
 * .tbd stub at runtime. */
#ifndef _TIL_SHIM_COREVIDEO_H
#define _TIL_SHIM_COREVIDEO_H

#include <stdint.h>
#include <CoreGraphics/CoreGraphics.h>

typedef int32_t CVReturn;
typedef struct __CVDisplayLink *CVDisplayLinkRef;
typedef uint64_t CVOptionFlags;

#endif /* _TIL_SHIM_COREVIDEO_H */
