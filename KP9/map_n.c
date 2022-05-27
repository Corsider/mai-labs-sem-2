#include "map_n.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


Map *map_create() {
    Map *m = (Map *)malloc(sizeof(Map));
    m->size = 0;
    m->sorted = 0;
    return m;
}

int map_size(Map *m) {
    return m->size;
}

void map_delete(Map *m) {
    free(m);
}

void map_pushBack(Map *m, char *key, char *value) {
    mapitem *item = (mapitem *)malloc(sizeof(mapitem));
    strcpy(item->key, key);
    strcpy(item->value, value);
    m->maps[map_size(m)] = item;
    m->size++;
}

int int_len(int x) {
    if (x == 0) {
        return 1;
    }
    return floor(log10(abs(x))) + 1;
}


void map_read(Map *m, FILE *f) {
    char str[LEN];
    char key[LEN]; //key[4];
    int keyi;
    int count = 0;
    while (!feof(f)) {
        for (int k = 0; k < KEY_STR_LEN - 1; k++) {
            fscanf(f, "%c", &(key[k]));
        }
        for (int k = KEY_STR_LEN - 1; k < KEY_STR_LEN + KEY_INT_LEN; k++) {
            fscanf(f, "%c", &(key[k]));
        }
        //fscanf(f, "%d", &keyi);
        fseek(f, 1, SEEK_CUR);
        //for (int i = 0; i != int_len(keyi); i++) {
        //    key[4 + i] = keyi / pow(10, i);
        //}
        fscanf(f, "%c", &str[count]);
        while (str[count] != '\n' && !feof(f)) {
            count++;
            fscanf(f, "%c", &str[count]);
        }
        str[count] = '\0';
        count = 0;
        map_pushBack(m, key, str);
        memset(str, '\0', LEN);
    }
}

void map_print(Map *m) {
    printf("+--------+-----------------------+\n");
    printf("|  key   |       value           |\n");
    printf("+--------+-----------------------+\n");
    for (int i = 0; i != map_size(m); i++) {
        printf("| %-3s |    %-15s    |\n", m->maps[i]->key, m->maps[i]->value);
        printf("+--------+-----------------------+\n");
    }
}

void map_bin_search(Map *m, char *key) {
    if (strlen(key) != KEY_INT_LEN + KEY_STR_LEN) {
        printf("Key size is not equal to program's built-in size.\n\n");
    } else {
        int left = 0;
        int right = map_size(m) - 1;
        while (left < right - 1) {
            int mid = (left + right) / 2;
            if (strcmp(m->maps[mid]->key, key) < 0) {
                left = mid;
            } else {
                right = mid;
            }
            //printf("left %d mid %d right %d\n", left, mid, right);
        }
        //printf("right is %d. printig element %s\n", right, m->maps[right]->key);
        //printf("KEYSS %s %s \n", m->maps[right]->key, key);
        if (strcmp(m->maps[right]->key, key)) {
            printf("\nNo such element.\n\n");
        } else {
            printf("+--------+-----------------------+\n");
            printf("|  key   |       value           |\n");
            printf("+--------+-----------------------+\n");
            printf("| %-3s |    %-15s    |\n", m->maps[right]->key, m->maps[right]->value);
            printf("+--------+-----------------------+\n");
            printf("\n");
        }
    }
}

int cmp(const mapitem *i1, const mapitem *i2) {
    char *s1, *s2;
    strcpy(s1, i1->value);
    strcpy(s2, i2->value);
    int ok = 1; //i1 < i2
    for (int i = 0; i < KEY_STR_LEN + KEY_INT_LEN - 1; i++) {
        if (!((int)s1[i] < (int)s2[i])) {
            ok = 0;
            break;
        }
    }
    printf("cmp end\n");
    return ok;
}

void map_sort(Map *m) {
    printf("\nBefore sort:\n\n");
    map_print(m);
    printf("\n");
    int counter;

    int map_sz = map_size(m);
    for (int i = 0; i < map_sz - 1; i++) {
        mapitem *min = m->maps[i];
        counter = i;
        for (int j = i; j < map_sz; j++) {
            //printf("i - %d, j - %d, checking...\n", i, j);
            if (strcmp(m->maps[j]->key, min->key) < 0) {
                //printf("%s is < than %s\n", m->maps[j]->key, min->key);
                min = m->maps[j];
                counter = j;
            }
        }
        mapitem *buf = (mapitem *)malloc(sizeof(mapitem));
        strcpy(buf->key, m->maps[i]->key);
        strcpy(buf->value, m->maps[i]->value);
        m->maps[i] = min;
        m->maps[counter] = buf;
    }
    printf("After sort:\n\n");
    map_print(m);
    m->sorted = 1;
}

/*
int map_find(Map *m, char *key) {
    for (int i = 0; i < map_size(m); i++) {
        if (!strcmp(m->maps[i], key)) {
            return 1;
        }
    }
    return 0;
}
*/