#ifndef STR_H
#define STR_H

#include "aliases.h"

typedef struct {
    char *c_str;
    I64 cap;
} Str;

Str Str_val(const char *data);
Str *Str_new(const char *data);
Str *Str_new_len(const char *data, I64 len);
Str *Str_clone(Str *s);
void Str_delete(Str *s);
Bool Str_eq(Str *a, Str *b);
Bool Str_eq_c(Str *a, const char *b);
I64 Str_cmp(Str *a, Str *b);
Str *Str_concat(Str *a, Str *b);
Str *Str_to_str(Str *s);
I64 Str_len(Str *s);
Str *Str_substr(Str *s, I64 start, I64 len);
Bool Str_contains(Str *a, Str *b);
Bool Str_starts_with(Str *a, Str *b);
Bool Str_ends_with(Str *a, Str *b);
Bool Str_neq(Str *a, Str *b);
Bool Str_is_empty(Str *s);
I64 Str_find(Str *s, Str *needle);
I64 Str_rfind(Str *s, Str *needle);
Str *Str_replace(Str *s, Str *from, Str *to);
Str *Str_get_char(Str *s, I64 i);
Str *Str_strip_prefix(Str *s, Str *prefix);
Str *Str_strip_suffix(Str *s, Str *suffix);
Str *Str_from_byte(U8 byte);
I64 Str_to_i64(Str *s);

#endif
