#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

Iterator prevOLD(List *ls, Iterator *i) {
    Iterator ii = first(ls);
    Iterator nii = next(&ii);
    for (Iterator k = nii; k.part != i->part; k = next(&k)) {
        ii = k;
    }
    return ii;
}

Iterator prev(List *ls, Iterator *i) {
    Iterator ii;
    for (Iterator j = first(ls); j.part != i->part; j = next(&j)) {
        ii = j;
    }
    return ii;
}

Iterator prevOLD3(List *ls, Iterator *i) {
    Iterator res = first(ls);
    while (strcmp(ls->start->next->str, i->part->str) != 0) {
        res = next(&res);
    }
    return res;
}

Iterator prevOLD4(List *ls, Iterator *i) {
    Iterator res;
    for (Iterator j = first(ls); j.part != i->part; j = next(&j)) {
        res = j;
    }
    return res;
}



Iterator first(List *ls) {
    Iterator i = {ls->start};
    return i;
}

Iterator end(List *ls) {
    Iterator i = first(ls);
    //i.part = ls->start;
    return i;
}

Iterator last(List *ls) {
    Iterator counter = first(ls);
    Iterator res = first(ls);
    counter = next(&counter);
    //printf("[LAST]: next of first is %s\n", counter.part->str);
    for (Iterator i = counter; i.part != end(ls).part; i = next(&i)) {
        res = i;
    }
    return res;
}

Iterator insert(List *ls, Iterator *i, char *data) {
    Iterator toPaste = {(struct Item *) malloc(sizeof(struct Item))};
    strcpy(toPaste.part->str, data);
    ls->size++;
    if (ls->start == NULL) { //i->part
        ls->start = toPaste.part;
        ls->start->next = ls->start; //changed
        //printf("[INSERT] added root elem, its next is %s\n", ls->start->next->str);
        return toPaste;
    } else {
        toPaste.part->next = i->part->next;
        i->part->next = toPaste.part; // i -> toPaste -> iNext ...
        return toPaste;
    }
}

Iterator deleteOLD(List *ls, Iterator *i) {
    if (i->part == ls->start) {
        Iterator lst = last(ls);
        Iterator fst = first(ls);
        fst = next(&fst);
        lst.part->next = fst.part;
        free(i->part);
        ls->size--;
        Iterator res = {ls->start};
        return res;
    } else {
        Iterator pre = prev(ls, i);
        Iterator nxt = next(i);
        pre.part->next = nxt.part;
        free(i->part);
        return pre;
    }
}

Iterator delete(List *ls, Iterator *i) {
    if (i->part == ls->start) { // if deleting first elem
        Iterator lst = last(ls);
        lst.part->next = ls->start->next;
        free(i->part);
        ls->start = lst.part->next;
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
        ls->start->next = ls->start; //changed
        //printf("[PUSH BACK] next of start is %s\n", ls->start->next->str);
        return temp;
    } else {
        temp.part->next = ls->start; //changed
        last(ls).part->next = temp.part; // inserting after last iter
        return temp;
    }
}

Iterator find(List *ls, char *data) {
    Iterator res = {NULL};
    if (!strcmp(ls->start->str, data)) {
        res = first(ls);
        return res;
    }
    Iterator comp = first(ls);
    for (int i = 0; i < ls->size; i++) {
        comp = next(&comp);
        if (!strcmp(comp.part->str, data)) {
            res = comp;
            break;
        }
    }
    return res;
}

void print_connection(List *ls) {
    printf("List length: %d\n", ls->size);
    Iterator x = first(ls);
    for (int i = 0; i < list_length(ls); i++) {
        //Item it = x.part->next;
        Iterator xn;
        xn.part = x.part->next;
        printf("Elem %s, it's next is %s\n", x.part->str, xn.part->str);
        x = next(&x);
    }
}

void list_print(List *ls) {
    if (list_length(ls) > 0) {
        printf("%s ", ls->start->str);
        Iterator j = first(ls);
        for (Iterator i = next(&j); i.part != end(ls).part; i = next(&i)) {
            printf("%s ", i.part->str);
        }
    }
    
    printf("\n");
}

int list_function(List *ls, char *elem) {
    Iterator i = find(ls, elem);
    if (i.part != NULL) {
        printf("Found %s in list. Deleting list...\n", elem);
        list_destroy(ls);
        printf("\n");
        return 1;
    } else {
        printf("No such element was found.\n\n");
        return 0;
    }
}

int list_length(List *ls) {
    return ls->size;
}

void list_forceFirstElem(List *ls, char *data) {
    Iterator f = first(ls);
    strcpy(f.part->str, data);
}

void list_destroy(List *ls) {
    Iterator i = first(ls);
    while (list_length(ls) != 0) {
        i = delete(ls, &i);
    }
    ls->size = 0;
}