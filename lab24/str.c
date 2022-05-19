#include "str.h"
#include <stdio.h>
#include <string.h>

void st_create(String *str) {
    str->data = (char *) malloc(STR_LEN + 1);
    str->alloc = STR_LEN;
    memset(str->data, 0, str->alloc + 1);
    str->length = 0;
}