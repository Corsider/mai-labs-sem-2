#ifndef _DEQUE_H_
#define _DEQUE_H_

typedef struct dequenode {
    int data;
    struct dequenode *next;
    struct dequenode *prev;
} Dequenode;

typedef struct {
    int count;
    Dequenode *top;
    Dequenode *bot;
} Deque;

Deque *create_deque();
Dequenode *createNode(int item);
void *push_front(Deque* deq, int item);
void *push_back(Deque* deq, int item);
void *pop_front(Deque* deq);
void *pop_back(Deque* deq);
int isEmpty(Deque* deq);
int getFront(Deque* deq);
int getBack(Deque* deq);
void freeDeque(Deque *deq);
void printDequeRec(Deque *deq);
void quicksort(Deque *deq, int left, int right);

//
//int getElementByIndex(Dequenode *deq, int index, int iter);
//void concatenate(Deque *deq1, Deque *deq2);
//Deque *cutDeque(Deque *deq, int start, int finish);
//void setDeqElementByIndex(Deque *deq, int index, int value);

//todelete
//int getDeqElementByLeftIndex(Deque *deq, int index);

#endif