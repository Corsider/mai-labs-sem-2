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



Iterator first(List *ls) {
    Iterator i = {ls->start};
    return i;
}

Iterator end(List *ls) {
    Iterator i;
    i.part = ls->start;
    return i;
}

Iterator pre_end(List *ls) {
    Iterator i;
    for (Iterator j = first(ls); j.part->next != ls->start; j = next(&j)) {
        i = j;
    }
    return i;
}

Iterator last(List *ls) {
    Iterator i;
    for (Iterator j = first(ls); j.part != end(ls).part; j = next(&j)) {
        i = j;
    }
    return i;
}

//char *get_data(Iterator *i) {
//    return i->part->str;
//}

Iterator insert(List *ls, Iterator *i, char *data) {
    Iterator toPaste = {(struct Item *) malloc(sizeof(struct Item))};
    strcpy(toPaste.part->str, data);
    ls->size++;
    if (i->part == NULL) {
        ls->start = toPaste.part;
        ls->start->next = ls->start; //changed
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
        //update ptrs to first elem from last ...
        Iterator last = end(ls);
        Iterator pre_last = prev(ls, &last);
        //printf("Last elem needs adj ptrs. elem: %s\n", pre_last.part->str);
        pre_last.part->next = res.part;
        printf("updated. elem %s to elem %s\n", end(ls).part->str, first(ls).part->str);
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
        return temp;
    } else {
        temp.part->next = ls->start; //changed
        last(ls).part->next = temp.part; // inserting after last iter
        return temp;
    }
}

Iterator find(List *ls, char *data) {
    Iterator result = {NULL};
    //printf("start is %s\n", ls->start->str);
    if (!strcmp(ls->start->str, data)) {
        return first(ls);
    }
    Iterator ed = end(ls);
    Iterator pre = prev(ls, &ed);
    //Iterator pre = pre_end(ls);
    //printf("pre-last elem is %s\n", pre.part->str);
    //printf("Started comparing. first: %s last(pre): %s\n", first(ls).part->str, pre.part->str);
    for (Iterator i = first(ls); i.part != pre.part; i = next(&i)) {
        //printf("comparing %s and %s, flag %s ...\n", i.part->str, data, pre.part->str);
        if (!strcmp(i.part->str, data)) {
            result = i;
            break;
        }
        /*
        int cont;
        scanf("%d", &cont);
        if (cont == 1) {
            continue;
        } else {
            break;
        }
        */
    }
    //check last elem
    if (!strcmp(pre.part->str, data)) {
        //printf("Here\n");
        result = pre;
    }
    return result;
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

void lsp(List *ls, char *start) {
    printf("%s ", ls->start->str);
    if (ls->start->next->str != start) {
        lsp(ls, start);
    }
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


void list_destroy(List *ls) {
    Iterator i = first(ls);
    while (list_length(ls) != 0) {
        i = delete(ls, &i);
    }
    ls->size = 0;
}