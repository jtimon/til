#ifndef STR_H
#define STR_H

typedef struct {
    char *c_str;
    int len;
} Str;

// Construction / destruction
Str Str_val(const char *data);  // returns Str by value (for struct fields)
Str *Str_new(const char *data);
Str *Str_new_len(const char *data, int len);
Str *Str_clone(Str *s);
void Str_delete(Str *s);

// til interface
int Str_eq(Str *a, Str *b);
int Str_eq_c(Str *a, const char *b);
Str *Str_concat(Str *a, Str *b);
Str *Str_to_str(Str *s);

// Extra
int Str_len(Str *s);
Str *Str_substr(Str *s, int start, int len);
int Str_contains(Str *a, Str *b);
int Str_starts_with(Str *a, Str *b);
int Str_ends_with(Str *a, Str *b);

#endif
