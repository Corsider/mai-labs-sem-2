#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

List *list_create() {
    List *l = (List *)malloc(sizeof(List));
    l->start = NULL;
    l->size = 0;
    return l;
}

int list_size(List *ls) {
    return ls->size;
}

Iterator next(Iterator *i) {
    Iterator ii = {i->part->next};
    return ii;
}

Iterator prev(List *ls, Iterator *i) {
    Iterator ii;
    for (Iterator j = first(ls); j.part != i->part; j = next(&j)) {
        ii = j;
    }
    return ii;
}

Iterator first(List *ls) {
    Iterator i = {ls->start};
    return i;
}

Iterator end(List *ls) {
    Iterator i = {NULL};
    return i;
}

Iterator last(List *ls) {
    Iterator i;
    for (Iterator j = first(ls); j.part != end(ls).part; j = next(&j)) {
        i = j;
    }
    return i;
}

char *get_data(Iterator *i) {
    return i->part->str;
}

Iterator insert(List *ls, Iterator *i, char *data) {
    Iterator toPaste = {(struct Item *) malloc(sizeof(struct Item))};
    strcpy(toPaste.part->str, data);
    ls->size++;
    if (i->part == NULL) {
        ls->start = toPaste.part;
        ls->start->next = NULL;
        return toPaste;
    } else {
        toPaste.part->next = i->part->next;
        i->part->next = toPaste.part; // i -> toPaste -> iNext ...
        return toPaste;
    }
}

Iterator delete(List *ls, Iterator *i) {
    if (i->part == ls->start) { // if deleting first elem
        struct Item *t = {ls->start->next};
        free(i->part);
        ls->start = t;
        Iterator res = {ls->start};
        ls->size--;
        return res;
    } else {
        Iterator prv = prev(ls, i); // getting previous
        prv.part->next = i->part->next; // prv -> *something deleted* -> *deleted->next*
        free(i->part);
        ls->size--;
        return prv;
    }
}

Iterator push_back(List *ls, char *data) {
    Iterator temp = {(struct Item*)malloc(sizeof(struct Item))};
    strcpy(temp.part->str, data);
    ls->size++;
    if (ls->start == NULL) {
        ls->start = temp.part;
        ls->start->next = NULL;
        return temp;
    } else {
        temp.part->next = NULL;
        last(ls).part->next = temp.part; // inserting after last iter
        return temp;
    }
}
/*
int list_length_int(List *ls, char *startC, int start) {
    start++;
    if (ls->next->data != startC) {
        list_length_int(ls->next, startC, start);
    }
    return start;
}
*/
/*
int list_length(List *ls) {
    //int *x = 0;
    //list_length_int(ls, x);
    //return list_length_int(ls, ls->data, 0);
    int res = 0;
    char *check = ls->data;
    List *qurrent = ls;
    while (qurrent->next->data != check) {
        res++;
        qurrent = qurrent->next;
    }
    return res+1;
}

void list_print_internal(List *ls, char *start) {
    printf("%s ", ls->data);
    if (ls->next->data != start) {
        list_print_internal(ls->next, start);
    }
}

void list_print(List *ls) {
    printf("[INT] Recieved list->data = %s\n", ls->data);
    list_print_internal(ls, ls->data);
    printf("\n");
}

void list_add(List *ls, char *elem) {
    List *knot = list_create(elem);
    List *buffer = ls->next;
    ls->next = knot;
    knot->next = buffer;
}

void list_remove(List *ls, char *elem) {
    List *t = ls;
    while (t->next->data != elem) {
        t = t->next;
    }
    List *after = t->next->next;
    t->next = after;
    //list_destroy(elem);
}

void list_function(List *ls, char *elem) {
    List *t = ls;
    int found = 0;
    while (t->next->data != ls->data) {
        if (t->data == elem) {
            found = 1;
            break;
        }
        t = t->next;
    }
    if (found) {
        printf("Found this element. Deleting list...\n");
        list_destroy(ls);
    } else {
        printf("Nothing.\n");
    }
}

int list_find(List *ls, char *elem) {
    List *t = ls;
    int found = 0;
    while (t->next->data != ls->data) {
        if (t->data == elem) {
            found = 1;
            break;
        }
        t = t->next;
    }
    if (found) {
        return 1;
    } else {
        return 0;
    }
}
*/
void list_destroy(List *ls) {
    free(ls);
    ls = NULL;
}