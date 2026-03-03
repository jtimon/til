#ifndef TIL_EXT_H
#define TIL_EXT_H

void til_free(void *ptr);
void til_exit(long long *code);
const char **til_i64_to_str(long long *v);
const char **til_u8_to_str(unsigned char *v);
int *til_str_eq(const char **a, const char **b);

#endif
