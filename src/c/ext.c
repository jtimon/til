#include "ext.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void til_free(void *ptr) { free(ptr); }
void til_exit(long long *code) { exit((int)*code); }

const char **til_i64_to_str(long long *v) {
    char *buf = malloc(32);
    snprintf(buf, 32, "%lld", *v);
    const char **r = malloc(sizeof(const char *));
    *r = buf;
    return r;
}

const char **til_u8_to_str(unsigned char *v) {
    char *buf = malloc(4);
    snprintf(buf, 4, "%u", (unsigned)*v);
    const char **r = malloc(sizeof(const char *));
    *r = buf;
    return r;
}

int *til_str_eq(const char **a, const char **b) {
    int *r = malloc(sizeof(int));
    *r = (strcmp(*a, *b) == 0);
    return r;
}
