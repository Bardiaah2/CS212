#ifndef proj3A_deque_h
#define proj3A_deque_h

typdef struct{
    void *data;
    struct Node *next;
    struct Node *perv;
} Node;


typdef struct{
    int count;
    Node *front;
    Node *back;
} Deque;

tyodef void (*printData)(void *);

Node *newNode(void *data, size_t dataSize);
Deque *createDeque();
void insertFront(Deque *deque, void *data, size_t dataSize);
void insertBack(Deque *deque, void *data, size_t dataSize);
void removeFront(Deque *deque, void *data, size_t dataSize);
void removeBack(Deque *deque, void *data, size_t dataSize);
void freeDeque(Deque *deque);
void printDeque(Deque *deque, printData print);
