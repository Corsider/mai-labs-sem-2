#ifndef LIST_H
#define LIST_H

#define STRING_SIZE 100
//хранить дату в фиксированном массиве data[100]
typedef struct List {
    char data[STRING_SIZE];
    struct List *next;
} List;

List *list_create(char *data);
void list_print(List *ls);
void list_add(List *ls, char *elem);
void list_remove(List *ls, char *elem);
void list_function(List *ls, char *elem);
int list_length(List *ls);
int list_find(List *ls, char *elem);
void list_destroy(List *ls);

#endif