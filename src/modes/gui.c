#include "ext.h"
#include <raylib.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

void draw_text(Str *text, I64 *x, I64 *y, I64 *font_size,
                   I64 *r, I64 *g, I64 *b, I64 *a) {
    char *t = strndup((char *)text->data, text->cap);
    DrawText(t, (int)*x, (int)*y, (int)*font_size,
             (Color){(unsigned char)*r, (unsigned char)*g,
                     (unsigned char)*b, (unsigned char)*a});
    free(t);
}

I64 *get_screen_width(void) {
    I64 *r = malloc(sizeof(I64));
    *r = GetScreenWidth();
    return r;
}

I64 *get_screen_height(void) {
    I64 *r = malloc(sizeof(I64));
    *r = GetScreenHeight();
    return r;
}

I64 *get_frame_time(void) {
    I64 *r = malloc(sizeof(I64));
    *r = (I64)(GetFrameTime() * 1000);
    return r;
}

Bool *is_key_pressed(I64 *key) {
    Bool *r = malloc(sizeof(Bool));
    *r = IsKeyPressed((int)*key);
    return r;
}

Bool *is_key_down(I64 *key) {
    Bool *r = malloc(sizeof(Bool));
    *r = IsKeyDown((int)*key);
    return r;
}

void draw_circle(I64 *cx, I64 *cy, I64 *radius,
                     I64 *r, I64 *g, I64 *b, I64 *a) {
    DrawCircle((int)*cx, (int)*cy, (float)*radius,
               (Color){(unsigned char)*r, (unsigned char)*g,
                        (unsigned char)*b, (unsigned char)*a});
}

I64 *get_random_value(I64 *min, I64 *max) {
    I64 *r = malloc(sizeof(I64));
    *r = GetRandomValue((int)*min, (int)*max);
    return r;
}

I64 *get_mouse_x(void) {
    I64 *r = malloc(sizeof(I64));
    *r = GetMouseX();
    return r;
}

I64 *get_mouse_y(void) {
    I64 *r = malloc(sizeof(I64));
    *r = GetMouseY();
    return r;
}

Bool *is_mouse_button_pressed(I64 *button) {
    Bool *r = malloc(sizeof(Bool));
    *r = IsMouseButtonPressed((int)*button);
    return r;
}

void init_audio_device(void) { InitAudioDevice(); }
void close_audio_device(void) { CloseAudioDevice(); }

static Sound prev_tone = {0};
static bool tone_loaded = false;

void play_tone(I64 *freq, I64 *duration_ms) {
    if (tone_loaded) UnloadSound(prev_tone);
    int sr = 44100;
    int n = sr * (int)*duration_ms / 1000;
    if (n < 1) n = 1;
    float *data = malloc(n * sizeof(float));
    int attack = sr / 100;  // 10ms
    int release = sr / 100;
    for (int i = 0; i < n; i++) {
        float env = 1.0f;
        if (i < attack) env = (float)i / attack;
        if (i > n - release) env = (float)(n - i) / release;
        data[i] = sinf(2.0f * 3.14159265f * (float)*freq * (float)i / sr) * 0.3f * env;
    }
    Wave w = { .frameCount = n, .sampleRate = sr, .sampleSize = 32, .channels = 1, .data = data };
    prev_tone = LoadSoundFromWave(w);
    PlaySound(prev_tone);
    tone_loaded = true;
    free(data);
}
