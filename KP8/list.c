#include "list.h"
#include <stdio.h>
#include <stdlib.h>

List *list_create(char *data) {
    List *l = (List *)malloc(sizeof(List));
    l->data = &data;
    l->next = l;
    return l;
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

void list_destroy(List *ls) {
    free(ls);
    ls = NULL;
}