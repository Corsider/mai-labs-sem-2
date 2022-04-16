#include "deque.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check(char *c) {
    while (*c) {
        if ((*c < '0' || *c > '9') && (*c != '-') && (*c != '.')) {
            return 0;
        }
        *c++;
    }
    return 1;
}

void throw_error() {
    printf("\n");
    printf("%s\n", "ERROR - Invalid input");
    printf("\n");
}

int main(void)
{
    Deque *deq = create_deque();
    int deqCreated = 0;

    //menu
    while (1) {
        printf("%s\n", "What do you want to do?");
        printf("%s\n", "1) Add something to deque");
        printf("%s\n", "2) Remove something from deque");
        printf("%s\n", "3) Print deque");
        printf("%s\n", "4) Sort");
        printf("%s\n", "5) Exit");
        printf("%s", "? - ");
        char c[100] = "";
        char c1[100] = "";
        scanf("%s", c);
        if (!check(c)) {
            throw_error();
            continue;
        }
        //printf("\n");
        
        if (!strcmp(c, "1")) {
            int value;
            printf("How to insert a new value: <h> or <t> (head, tail), then <value>\n");
            scanf("%s", c);
            scanf("%s", c1);
            if (!check(c1)) {
                throw_error();
                continue;
            }
            value = atoi(c1);
            if (!strcmp(c, "h")) {
                push_front(deq, value);
            } else if (!strcmp(c, "t")) {
                push_back(deq, value);
            } else {
                printf("\n");
                printf("No such option\n");
                printf("\n");
                continue;
            }
            printf("\nInsert result:\n");
            printDequeRec(deq);
            printf("\n");
            deqCreated = 1;
        } else if (!strcmp(c, "2")) {
            if (deqCreated == 1) {
                printf("\n");
                printf("How to delete a value: <h> or <t> (head, tail)\n");
                scanf("%s", c);
                if (!strcmp(c, "h")) {
                    pop_front(deq);
                } else if (!strcmp(c, "t")) {
                    pop_back(deq);
                } else {
                    printf("\n");
                    printf("No such option\n");
                    printf("\n");
                    continue;
                }
                printf("\n");
                if (!isEmpty(deq)) {
                    printf("Deletion result:\n");
                    printDequeRec(deq);
                    printf("\n");
                } else {
                    deqCreated = 0;
                }
            } else {
                printf("\n");
                printf("Deque is empty\n");
                printf("\n");
                continue;
            }
        } else if (!strcmp(c, "3")) {
            printf("\n");
            if (!isEmpty(deq)) {
                printDequeRec(deq);
                printf("\n");
            } else {
                printf("Deque is empty\n");
                printf("\n");
                continue;
            }
        } else if (!strcmp(c, "4")) {
            if (!isEmpty(deq)) {
                printf("\n");
                printf("Sorting...\n");
                quicksort(deq, 0, deq->count - 1);
                printDequeRec(deq);
                printf("\n");
            } else {
                printf("\nDeque is empty\n");
                printf("\n");
                continue;
            }
        } else if (!strcmp(c, "5")) {
            printf("\nExiting...\n");
            break;
        } else {
            printf("%s", "No such option\n");
            printf("\n");
        }
    }
    //////////////////////////////////////
    /*
    push_front(deq, 5);
    push_front(deq, 4);
    push_back(deq, 1);
    push_back(deq, 3);
    push_back(deq, -9);
    printDequeRec(deq);
    //quicksort(deq, 0, deq->count);
    //printf("NEW GET 1: %d\n", getElementByIndex(deq->top, 0, 0));
    quicksort(deq, 0, deq->count - 1);
    //setDeqElementByIndex(deq, 2, 8);
    printDequeRec(deq);
    */
    freeDeque(deq);
    return 0;
}