#include "ext.h"
#include <stdlib.h>

void til_free(void *ptr) { free(ptr); }
void til_exit(long long *code) { exit((int)*code); }
