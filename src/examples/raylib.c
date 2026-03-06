#include "ccore.h"
#include "ext.h"
#include <raylib.h>
#include <stdlib.h>
#include <string.h>

void til_init_window(til_I64 *w, til_I64 *h, til_Str *title) {
    char *t = strndup((char *)title->data, title->cap);
    InitWindow((int)*w, (int)*h, t);
    free(t);
}

til_Bool *til_window_should_close(void) {
    til_Bool *r = malloc(sizeof(til_Bool));
    *r = WindowShouldClose();
    return r;
}

void til_begin_drawing(void) { BeginDrawing(); }
void til_end_drawing(void) { EndDrawing(); }
void til_close_window(void) { CloseWindow(); }

void til_clear_background(til_I64 *r, til_I64 *g, til_I64 *b, til_I64 *a) {
    ClearBackground((Color){(unsigned char)*r, (unsigned char)*g,
                            (unsigned char)*b, (unsigned char)*a});
}

void til_set_target_fps(til_I64 *fps) { SetTargetFPS((int)*fps); }

void til_draw_rectangle(til_I64 *x, til_I64 *y, til_I64 *w, til_I64 *h,
                        til_I64 *r, til_I64 *g, til_I64 *b, til_I64 *a) {
    DrawRectangle((int)*x, (int)*y, (int)*w, (int)*h,
                  (Color){(unsigned char)*r, (unsigned char)*g,
                          (unsigned char)*b, (unsigned char)*a});
}
