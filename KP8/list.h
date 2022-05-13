#ifndef LIST_H
#define LIST_H

#define STRING_SIZE 100

typedef struct Item {
    char str[STRING_SIZE];
    struct Item *next;
} Item;

typedef struct Iterator {
    struct Item *part;
} Iterator;

typedef struct List {
    //char data[STRING_SIZE];
    struct Item *start;
    int size;
    //struct List *next;
} List;

Iterator next(Iterator *i);
Iterator prev(List *ls, Iterator *i);
Iterator first(List *ls);
Iterator last(List *ls);
Iterator add(List *ls, Iterator *i, char *data);
Iterator delete(List *ls, Iterator *i);
Iterator find(List *ls, char *data);
Iterator push_back(List *ls, char *data);

List *list_create();
void list_print(List *ls);
//void list_add(List *ls, char *elem);
//void list_remove(List *ls, char *elem);
void list_function(List *ls, char *elem);
int list_length(List *ls);
//int list_find(List *ls, char *elem);
void list_destroy(List *ls);
char *get_data(Iterator *i);

#endif