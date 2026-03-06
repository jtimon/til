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

void til_draw_text(til_Str *text, til_I64 *x, til_I64 *y, til_I64 *font_size,
                   til_I64 *r, til_I64 *g, til_I64 *b, til_I64 *a) {
    char *t = strndup((char *)text->data, text->cap);
    DrawText(t, (int)*x, (int)*y, (int)*font_size,
             (Color){(unsigned char)*r, (unsigned char)*g,
                     (unsigned char)*b, (unsigned char)*a});
    free(t);
}

til_I64 *til_get_screen_width(void) {
    til_I64 *r = malloc(sizeof(til_I64));
    *r = GetScreenWidth();
    return r;
}

til_I64 *til_get_screen_height(void) {
    til_I64 *r = malloc(sizeof(til_I64));
    *r = GetScreenHeight();
    return r;
}

til_I64 *til_get_frame_time(void) {
    til_I64 *r = malloc(sizeof(til_I64));
    *r = (til_I64)(GetFrameTime() * 1000);
    return r;
}

til_Bool *til_is_key_pressed(til_I64 *key) {
    til_Bool *r = malloc(sizeof(til_Bool));
    *r = IsKeyPressed((int)*key);
    return r;
}

til_Bool *til_is_key_down(til_I64 *key) {
    til_Bool *r = malloc(sizeof(til_Bool));
    *r = IsKeyDown((int)*key);
    return r;
}
