/* Qualifiers on the pointer parameter itself do not qualify its target. */
void inspect(const int *data);
void replace(const int **slot);
void inspect_slot(int *const *slot);
void write_bytes(char *const data);
void replace_opaque(const void **slot);
typedef const int ReadInt;
typedef ReadInt StillReadInt;
int *write_result(void);
int *const write_result_fixed(void);
int const *read_result(void);
StillReadInt *read_alias(void);
void inspect_alias(StillReadInt *data);
typedef struct {
    int *change, *const fixed_change;
    const int *look, *const fixed_look;
    StillReadInt *look_alias;
} PointerFields;
