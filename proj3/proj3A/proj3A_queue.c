#include "proj3A_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initialize(Queue *q){
    // malloc the size of the pointers to the strings,
    q->array = malloc(INIT_SIZE * sizeof(char*));
    // then the size of the strings
    for (int i=0; i<INIT_SIZE; i++){
        q->array[i] = malloc(MAX_SIZE*sizeof(char));
        q->array[i][MAX_SIZE-1] = '\0';
    }

    //set values
    q->front = 0;
    q->rear = 0;
    q->size = 8;
    q->capacity = 8;
}

void cleanup(Queue *q){
    printf("Cleaning up Queue\n");
    for (int i=0; i<q->size; i++){
        free((q->array)[q->front]);
        q->front = (q->front + 1)%(q->size);
    }
    free(q->array);
}

int isFull(Queue *q){
    return (q->capacity == 0);
}

int isEmpty(Queue *q){
    return (q->capacity == q->size);
}

void resize(Queue *q){  // potentially wrong with the string
    printf("Resizing queue to %d\n", q->size * 2);
    //update memory
    char **new_array = malloc((q->size)*2*sizeof(char*));
    for (int _=0; _<2*q->size;_++){
        new_array[_] = malloc(MAX_SIZE*sizeof(char));
        new_array[_][MAX_SIZE-1] = '\n';
    }
    for (int _=0; _<q->size; _++){
        strncpy(new_array[q->front], q->array[q->front], MAX_SIZE);
        q->front = (q->front + 1) % q->size;
        free(q->array[q->front-1 + (q->size)*(q->front == 0)]);
    }

    free(q->array);
    q->array = new_array;

    // update attriibute
    q->front = q->rear;
    q->capacity += q->size;
    q->size *= 2;
    // update rear
    q->rear = ((q->front) + (q->size - q->capacity))%q->size;
}


void enqueue(Queue *q, char *value){
    if (!(q->capacity)){
        resize(q);
    }
    strncpy((q->array)[q->rear], value, MAX_SIZE);
    q->rear = (q->rear + 1) % q->size;
    q->capacity--; 

    printf("Enqueued (%d): %s\n", q->rear - 1+(q->size)*(q->rear==0), q->array[q->rear - 1+(q->size)*(q->rear==0)]);
}

char *dequeue(Queue *q){
    if (isEmpty(q)){
        printf("Queue is empty\n");
        return NULL;
    }
    char *result = q->array[q->front];
    q->front = (q->front + 1) % q->size;

    q->capacity++;
    printf("Dequeued (%d): %s\n", q->front-1 + (q->size)*(q->front==0), result);

    return result;
}

void printQueue(Queue *q){
    for (int i = 0; i<(q->size - q->capacity); i++){
          printf("%d: %s\n", (i+q->front)%q->size, q->array[(i+q->front)%q->size]);
    }
    printf("Capacity: %d, used: %d\n", q->size, (q->size - q->capacity));
}

