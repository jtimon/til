#include "ext.h"
#include <raylib.h>
#include <stdlib.h>
#include <string.h>

void init_window(I64 *w, I64 *h, Str *title) {
    char *t = strndup((char *)title->data, title->cap);
    InitWindow((int)*w, (int)*h, t);
    free(t);
}

Bool *window_should_close(void) {
    Bool *r = malloc(sizeof(Bool));
    *r = WindowShouldClose();
    return r;
}

void begin_drawing(void) { BeginDrawing(); }
void end_drawing(void) { EndDrawing(); }
void close_window(void) { CloseWindow(); }

void clear_background(I64 *r, I64 *g, I64 *b, I64 *a) {
    ClearBackground((Color){(unsigned char)*r, (unsigned char)*g,
                            (unsigned char)*b, (unsigned char)*a});
}

void set_target_fps(I64 *fps) { SetTargetFPS((int)*fps); }

void draw_rectangle(I64 *x, I64 *y, I64 *w, I64 *h,
                        I64 *r, I64 *g, I64 *b, I64 *a) {
    DrawRectangle((int)*x, (int)*y, (int)*w, (int)*h,
                  (Color){(unsigned char)*r, (unsigned char)*g,
                          (unsigned char)*b, (unsigned char)*a});
}
