#include "deque.h"
#include <stdio.h>
#include <stdlib.h>

Deque *create_deque() {
    Deque *deq = (Deque *) malloc(sizeof(Deque));
    deq->count = 0;
    deq->bot = NULL;
    deq->top = NULL;
    return deq;
}

int isEmpty(Deque *deq) {
    if (deq->count == 0) {
        return 1;
    } else {
        return 0;
    }
}

Dequenode *createNode(int item) {
    Dequenode *n = (Dequenode *) malloc(sizeof(Dequenode));
    n->data = item;
    n->next = n->prev = NULL;
    return n;
}
//front --- back
void *push_front(Deque *deq, int item) {
    Dequenode *tmp = createNode(item);
    tmp->next = deq->top;
    tmp->prev = NULL;
    if (!isEmpty(deq)) {
        deq->top->prev = tmp;
        deq->top = tmp;
    } else {
        deq->bot = deq->top = tmp;
    }
    deq->count++;
}

void freeDequeNode(Dequenode *deqn) {
    if (deqn != NULL) {
        freeDequeNode(deqn->next);
        freeDequeNode(deqn->prev);
        //deleted
        //free(deqn->data);
        deqn->next = NULL; //deleting field
        deqn->prev = NULL;
        free(deqn);
        deqn = NULL; //deleting node
    }
}

void freeDeque(Deque *deq) {
    while (deq->top != deq->bot) {
        Dequenode *nod = deq->top;
        deq->top = deq->top->next;
        deq->top->prev = 0;
        free(nod);
    }
    deq->bot = deq->top = 0;
    deq->count = 0;
    free(deq);
}

void *push_back(Deque *deq, int item) {
    Dequenode *tmp = createNode(item);
    tmp->prev = deq->bot;
    tmp->next = NULL;
    if (!isEmpty(deq)) {
        deq->bot->next = tmp;
        deq->bot = tmp;
    } else {
        deq->top = deq->bot = tmp;
    }
    deq->count++;
}

void *pop_front(Deque *deq) {
    Dequenode *n = deq->top;
    if (!isEmpty(deq) && deq->count != 1) {
        deq->top = n->next;
        deq->top->prev = NULL;
        deq->count--;
    } else if (isEmpty(deq) && deq->count != 1){
        deq->bot = deq->top = NULL;
    } else {
        freeDeque(deq);
    }
    free(n);
}

void *pop_back(Deque *deq) {
    Dequenode *n = deq->bot;
    if (!isEmpty(deq) && deq->count != 1) {
        deq->bot = n->prev;
        deq->bot->next = NULL;
        deq->count--;
    } else if (isEmpty(deq) && deq->count != 1) {
        deq->top = deq->bot = NULL;
    } else {
        freeDeque(deq);
    }//TODO
    free(n);
}

int getFront(Deque *deq) {
    return deq->top->data;
}

int getBack(Deque *deq) {
    return deq->bot->data;
}

void printDequeNode(Dequenode *d) {
    if (d->next != NULL) {
        printf("%d ", d->data);
        printDequeNode(d->next);
    }
}

void printDequeRec(Deque *deq) {
    printDequeNode(deq->top);
    printf("%d", deq->bot->data);
    printf("\n");
}

int getElementByIndex(Dequenode *deq, int index, int iter) {
    if (iter < index) {
        getElementByIndex(deq->next, index, iter + 1);
    } else {
        return deq->data;
    }

}

void concatenate(Deque *deq1, Deque *deq2) {
    for (int i = 0; i < deq2->count; i++) {
        push_back(deq1, getElementByIndex(deq2->top, i, 0));
    }
    freeDeque(deq2);
}

Deque *cutDeque(Deque *deq, int start, int finish) {
    Deque *result = create_deque();
    for (int i = start; i < finish+1; i++) {
        push_back(result, getElementByIndex(deq->top, i, 0));
    }
    return result;
}

void setDeqElementByIndex(Deque *deq, int index, int value) {
    if (index == 0) {
        deq->top->data = value;
    } else if (index == deq->count - 1) {
        deq->bot->data = value;
    } else {
        Deque *dl = cutDeque(deq, 0, index - 1);
        Deque *dr = cutDeque(deq, index + 1, deq->count - 1);
        Deque *val = create_deque();
        push_back(val, value);
        concatenate(dl, val);
        concatenate(dl, dr);
        //deq = dl;
        deq->bot = dl->bot;
        deq->top = dl->top;
        //freeDeque(dl);
    }
    
}

void quicksort(Deque *deq, int left, int right) {
    int pivot;
    pivot = getElementByIndex(deq->top, left, 0);
    int l = left;
    int r = right;
    while (left < right) {
        while ((getElementByIndex(deq->top, right, 0) >= pivot) && (left < right)) {
            right--;
        }
        if (left != right) {
            setDeqElementByIndex(deq, left, getElementByIndex(deq->top, right, 0));
            //setDeqElementByIndex(deq, left, getElementByIndex(deq->top, right, 0));
            left++;
        }
        while ((getElementByIndex(deq->top, left, 0) <= pivot) && (left < right)) {
            left++;
        }
        if (left != right) {
            setDeqElementByIndex(deq, right, getElementByIndex(deq->top, left, 0));
            right--;
        }
    }
    setDeqElementByIndex(deq, left, pivot);
    //ar[left] = pivot;
    pivot = left;
    left = l;
    right = r;
    if (left < pivot) {
        quicksort(deq, left, pivot - 1);
    }
    if (right > pivot) {
        quicksort(deq, pivot + 1, right);
    }
}