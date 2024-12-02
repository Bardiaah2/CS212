#include "proj3A_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    if (argc<3){
        printf("Please provide a file name and a delimiter\n");
        return 1;
    }

    FILE *file;
    file = fopen(argv[1], "r");

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *cat = malloc((filesize + 1) * sizeof(char));
    fread(cat, filesize * sizeof(char), 1, file);
    cat[filesize-1] = '\0';
    fclose(file);

    Queue q;
    initialize(&q);

    printf("\n=> First enqueuing pass\n");
    char *word = strtok(cat, argv[2]);
    while (word){
        enqueue(&q, word);
        word = strtok(NULL, argv[2]);
    }

    printf("\n=> Dequeuing all elements\n");
    while (!isEmpty(&q)){
        dequeue(&q);
    }

    printf("\n=> Second enqueuing pass\n");
    file = fopen(argv[1], "r");
    fread(cat, filesize * sizeof(char), 1, file);
    cat[filesize-1] = '\0';
    fclose(file);
    word = strtok(cat, argv[2]);
    while (word){
        enqueue(&q, word);
        word = strtok(NULL, argv[2]);
    }

    printf("\n=> Printing queue\n");
    printQueue(&q);

    printf("\n=> Calling Queue cleanup\n");
    cleanup(&q);
    free(cat);
}
