#include "str.h"
#include <stdio.h>

Str *til_greet(Str *name) {
    Str *hello = Str_new("hello ");
    Str *result = Str_concat(hello, name);
    Str_delete(hello);
    return result;
}

void til_greet_print(Str *name) {
    Str *hello = Str_new("hello ");
    Str *msg = Str_concat(hello, name);
    printf("%s\n", msg->c_str);
    Str_delete(msg);
    Str_delete(hello);
}
