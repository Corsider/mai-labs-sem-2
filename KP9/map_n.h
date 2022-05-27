#ifndef _MAP_H_
#define _MAP_H_

#include <string.h>
#include <stdio.h>
#define LEN 128
#define KEY_STR_LEN 4
#define KEY_INT_LEN 2

typedef struct mapitem {
    char key[10]; //10
    char value[LEN];
} mapitem;

typedef struct Map {
    int size;
    int sorted;
    mapitem *maps[LEN];
} Map;

Map *map_create();
void map_delete(Map *m);
int map_size(Map *m);
void map_pushBack(Map *m, char *key, char *value);
//void map_erase(Map *m, char *key);
void map_read(Map *m, FILE *f);
void map_print(Map *m);
void map_bin_search(Map *m, char *key);
void map_sort(Map *m);

#endif