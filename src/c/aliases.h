#pragma once

#include <stdbool.h>

typedef long long I64;
typedef unsigned long long U64;
typedef int I32;
typedef unsigned int U32;
typedef short I16;
typedef unsigned short U16;
typedef char I8;
typedef unsigned char U8;
typedef float F32;
typedef bool Bool;
typedef U32 USize;  // container sizes (count, cap, elem_size)

// During the USize migration, generated code should box size arguments using
// the alias-facing ABI rather than the source expression's numeric type.
#define USIZE_REF(x) ((void *)&(U32){(U32)(x)})
