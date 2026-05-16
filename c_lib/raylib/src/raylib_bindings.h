// Aggregate header for binding-generation. Pulls in raylib.h plus the
// `rcamera` helpers (declared in rcamera.h, which raylib.h does not
// include) so the generated til bindings cover the same surface the
// hand-written src/lib/raylib.til used to expose.
#include "raylib.h"
#include "rcamera.h"
