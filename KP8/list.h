#ifndef LIST_H
#define LIST_H

//#include <stdbool.h>

#define STRING_SIZE 100

typedef struct Item {
    char str[STRING_SIZE];
    struct Item *next;
} Item;

typedef struct Iterator {
    struct Item *part;
} Iterator;

typedef struct List {
    struct Item *start;
    int size;
} List;

Iterator next(Iterator *i);
Iterator prev(List *ls, Iterator *i);
Iterator first(List *ls);
Iterator last(List *ls);
Iterator insert(List *ls, Iterator *i, char *data);
Iterator delete(List *ls, Iterator *i);
Iterator find(List *ls, char *data);
Iterator push_back(List *ls, char *data);
//Iterator get_by_index(List *ls, int ind);
//int get_index_by_iterator(List *ls, Iterator *iter);

List *list_create();
void list_print(List *ls);
int list_function(List *ls, char *elem);
int list_length(List *ls);
void list_destroy(List *ls);
char *get_data(Iterator *i);
void print_connection(List *ls);
void list_forceFirstElem(List *ls, char *data);

#endif