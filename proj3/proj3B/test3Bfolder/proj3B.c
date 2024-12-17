#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "proj3B_deque.h"

#define MAX_LEN 256

void rmLastChar(char *string){
    int len = 0;
    while (string[len] != '\n'){
        len++;
    }
    string[len] = '\0';
}

int main(){
    Deque *dqString = createDeque();
    Deque *dqLongInt = createDeque();

    void printString(void *data){
        printf("%s", (char *)data);
    }

    void printLongInt(void *data){
        printf("%d", ((int *)data)[0]);
    }

    printData printStr = printString;
    printData println = printLongInt;

    int countInt = 0;
    int countStr = 0;

    char input[MAX_LEN] = "";
    char *endptr = malloc(MAX_LEN * sizeof(char));
    char *endptr2 = endptr;
    do{
        printf("Please enter an integer or a string (empty to exit): \n");
        fgets(input, MAX_LEN, stdin);
        rmLastChar(input);

        int num;
        if ((num = strtol(input, &endptr, 10)) == 0 && *endptr != '\0'){
            printf("You entered the string: \"%s\"\n", input);
            countStr++;

            if (countStr % 2 == 0){
                insertBack(dqString, input, sizeof(input) * 8);
            } else {
                insertFront(dqString, input, sizeof(input) * 8);
            }
        } else if (*endptr == '\0' && num != 0){
            printf("You entered the number: %d\n", num);
            countInt++;
            
            if (countInt % 2 == 0){
                insertBack(dqLongInt, &num, sizeof(long int));
            } else {
                insertFront(dqLongInt, &num, sizeof(long int));
            }
        }

    } while (strncmp(input, "", MAX_LEN));
    printf("\n");
    printf("Printing string deque\n");
    printDeque(dqString, printStr);
    printf("\n");

    printf("Printing long deque\n");
    printDeque(dqLongInt, println);
    printf("\n");

    char stringHolder[MAX_LEN] = "";
    long int numHolder = 0;

    printf("Removing string deque data using count\n");
    for(int _=0; _<countStr/2;_++){
		removeBack(dqString, (void *)stringHolder, sizeof(stringHolder));
		printf("Removing %s\n", stringHolder);
        removeFront(dqString, (void *)stringHolder, sizeof(stringHolder));
        printf("Removing %s\n", stringHolder);
    }
    printf("\n");

    printf("Removing long deque data using count\n");
    for (int _=0; _<countInt/2; _++){
		removeBack(dqLongInt, &numHolder, sizeof(long int));
		printf("Removing %d\n", (int)numHolder);
        removeFront(dqLongInt, &numHolder, sizeof(long int));
        printf("Removing %d\n", (int)numHolder);
    }

    freeDeque(dqString);
    freeDeque(dqLongInt);
    free(endptr2);

    return 0;

}
