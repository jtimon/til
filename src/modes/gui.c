#include "ext.h"
#include <raylib.h>
#include <stdlib.h>
#include <math.h>

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
