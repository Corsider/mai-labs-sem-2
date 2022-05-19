#ifndef _STR_H_
#define _STR_H_

#include <stdlib.h>

size_t STR_LEN = 4;

typedef struct {
    char *data;
    size_t length;
    size_t alloc;
} String;

void st_create(String *str);
void st_copy(String *src, String *dest);
void st_append(String *str, char c);
void st_destroy(String *str);

#endif