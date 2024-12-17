#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "proj3B_deque.h"

Deque *createDeque(){
    Deque *dq;
    dq = (Deque*)malloc(sizeof(int) + 2 * sizeof(Node));
    if (!dq){
        fprintf(stderr, "Error allocating memory to deque.\n");
        exit(EXIT_FAILURE);
    }
    dq->count = 0;
    
    dq->front = NULL;
    dq->back = NULL;

    return dq;
}

Node *newNode(void *data, size_t dataSize){
    Node *node = malloc(sizeof(void *) * 3);
    if (!node){
        fprintf(stderr, "Error allocating memory to node.\n");
        exit(EXIT_FAILURE);
    }
    node->data = malloc(dataSize);
    if (node->data == NULL){
        fprintf(stderr, "Error allocating memory for node data.\n");
        exit(EXIT_FAILURE);
    }
    memcpy(node->data, data, dataSize);
    node->next = NULL;
    node->prev = NULL;

    return node;
}

void insertFront(Deque *deque, void *data, size_t dataSize){
    // make new node
    Node *node = newNode((void *)data, dataSize);

    // 4 cases in total (front exists or not) * (count == 0 || 1)
    if (deque->front){
        node->next = deque->front;
        deque->front->prev = node;
        deque->front = node;
        if (deque->count == 1){
            deque->back = deque->front->next;
        }
    } else {
        deque->front = node;
        deque->back = deque->front;
        if (deque->back){
            deque->back->prev = deque->front;
            deque->front->next = deque->back;
        }
    }
    deque->count++;
}

void insertBack(Deque *deque, void *data, size_t dataSize){
    // make new node
    Node *node = newNode((void *)data, dataSize);

    if (deque->back){
        node->prev = deque->back;
        deque->back->next = node;
        deque->back = node;
        if (deque->count == 1){
            deque->front = deque->back->prev;
        }
    } else {
        deque->back = node;
        deque->front = deque->back;
        if (deque->front){
            deque->front->next = deque->front;
            deque->back->prev = deque->front;
        }
    }
    deque->count++;
}

void removeFront(Deque *deque, void *data, size_t dataSize){
    if (!deque->front){
        fprintf(stderr, "Front is already empty.\n");
        exit(EXIT_FAILURE);
    }
    memcpy(data, deque->front->data, dataSize);
    Node *temp = deque->front;
    // move fron to the next and free front
    if (deque->count == 1){
        deque->front = NULL;
        deque->back = NULL;
    } else {
        deque->front = deque->front->next;
        deque->front->prev = NULL;
    }
    free(temp->data);
    free(temp);
    deque->count--;
}

void removeBack(Deque *deque, void *data, size_t dataSize){
    if (!deque->back){
        fprintf(stderr, "Back is already empty.\n");
        exit(EXIT_FAILURE);
    }

    memcpy(data, deque->back->data, dataSize);
    Node *temp = deque->back;
    // move back to prev and free back
    if (deque->count == 1){
        deque->front = NULL;
        deque->back = NULL;
    } else {
        deque->back = deque->back->prev;
        deque->back->next = NULL;
    }
    free(temp->data);
    free(temp);
    deque->count--;
}

void freeDeque(Deque *deque){
    while (deque->front){
        deque->front = deque->front->next;
        free(deque->front->prev->data);
        free(deque->front->prev);
    }
    free(deque);
}

void printDeque(Deque *deque, printData print){
    Node *temp = deque->front;

    while (deque->front){
        print(deque->front->data);
        printf(" ");
        deque->front = deque->front->next;
    }
    printf("\n");
    deque->front = temp;
}

