/* SDK-less shim for <ApplicationServices/ApplicationServices.h> (issue
 * #25 / #232). An umbrella framework; raylib's RGFW backend reaches it
 * only for the CoreGraphics display/geometry API, so re-export that. */
#ifndef _TIL_SHIM_APPLICATIONSERVICES_H
#define _TIL_SHIM_APPLICATIONSERVICES_H

#include <CoreFoundation/CoreFoundation.h>
#include <CoreGraphics/CoreGraphics.h>

#endif /* _TIL_SHIM_APPLICATIONSERVICES_H */
