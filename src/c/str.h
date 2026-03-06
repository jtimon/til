#ifndef STR_H
#define STR_H

typedef struct {
    char *c_str;
    int cap;
} Str;

Str Str_val(const char *data);
Str *Str_new(const char *data);
Str *Str_new_len(const char *data, int len);
Str *Str_clone(Str *s);
void Str_delete(Str *s);
int Str_eq(Str *a, Str *b);
int Str_eq_c(Str *a, const char *b);
int Str_cmp(Str *a, Str *b);
Str *Str_concat(Str *a, Str *b);
Str *Str_to_str(Str *s);
int Str_len(Str *s);
Str *Str_substr(Str *s, int start, int len);
int Str_contains(Str *a, Str *b);
int Str_starts_with(Str *a, Str *b);
int Str_ends_with(Str *a, Str *b);
int Str_neq(Str *a, Str *b);
int Str_is_empty(Str *s);
int Str_find(Str *s, Str *needle);
int Str_rfind(Str *s, Str *needle);
Str *Str_replace(Str *s, Str *from, Str *to);
Str *Str_get_char(Str *s, int i);
Str *Str_strip_prefix(Str *s, Str *prefix);
Str *Str_strip_suffix(Str *s, Str *suffix);
Str *Str_from_byte(unsigned char byte);
long long Str_to_i64(Str *s);

#endif
