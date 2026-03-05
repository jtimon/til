#include "ccore.h"
#include "ext.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

til_Str *til_greet(til_Str *name) {
    const char *hello = "hello ";
    int hello_len = 6;
    til_Str *result = malloc(sizeof(til_Str));
    result->cap = hello_len + name->cap;
    result->data = malloc(result->cap);
    memcpy(result->data, hello, hello_len);
    memcpy(result->data + hello_len, name->data, name->cap);
    return result;
}

void til_greet_print(til_Str *name) {
    const char *hello = "hello ";
    int hello_len = 6;
    fwrite(hello, 1, hello_len, stdout);
    fwrite(name->data, 1, name->cap, stdout);
    putchar('\n');
}
