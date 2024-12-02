#ifndef proj3A_queue_h
#define proj3A_queue_h

#define INIT_SIZE 8
#define MAX_SIZE 256

typedef struct{
    int front;  // the index to the first item
    int rear;  // the index to the first empty spot
    int capacity;  // how many spots are left
    int size;  // how many spots there is open or not
    char** array;
}Queue;

void initialize(Queue* q);
void cleanup(Queue* q);
int isFull(Queue* q);
int isEmpty(Queue* q);
void resize(Queue* q);
void enqueue(Queue* q, char *value);
char *dequeue(Queue *q);
void printQueue(Queue *q);

#endif
