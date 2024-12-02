#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int isSeperator(char s);
char * slice(char *s, int right, int left);

int main(int argc, char *argv[]) {
    // enough arguments?
    if (argc < 3){
        printf("not enogh arguments.\n");
        return 1;
    }
    FILE *file;

    // file can be opened?
    if ((file = fopen(argv[1], "r")) == NULL){
        printf("\"%s\" is not a valid file.");
        exit(1);
    }

    // file size?
    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    //getting file content
    char *cat = malloc((filesize + 1) * sizeof(char));
    if (cat == NULL){
        printf("cat failed!\n");
        free(cat);
        fclose(file);
        return 1;
    }
    fread(cat, filesize * sizeof(char), 1, file);
    cat[filesize] = '\0';
    fclose(file);

    // two pointer aproach
    int right = 0;
    int left = 0;
    int *counts = malloc((argc -2) * sizeof(int));
    // setting counters to 0
    for (int i = 0; i<argc-2; i++){
        counts[i] = 0;
    }
    while (cat[right] != '\0' && cat[left] != '\0'){
        // increment right till cat[i] is a char
        if (isSeperator(cat[right])){
            right++;
            continue;
        }

        // increment left starting from right till cat[left] is not a char
        left = right;
        while (!isSeperator(cat[left])){
            left++;
        }

        // compare each of the given words to cat[right:left]
        for (int i = 2; i<argc; i++){
            if (strlen(argv[i]) != (left - right)){
                continue;
            }
            if (!strncmp(argv[i], slice(cat, right, left), strlen(argv[i]))){
                counts[i-2]++;
            }

        }
        left++;
        right = left;
    }
    free(cat);

    // print the results
    for (int i = 2; i<argc; i++){
        printf("The word \"%s\" occurs %d times.\n", argv[i], counts[i-2]);
    }
    free(counts);
}

int isSeperator(char s){
    if (s == '\n' || s == ' ' || s == ',' || s == '.'){
        return 1;
    } else {
        return 0;
    }
    return -1;
}

char * slice(char * s, int right, int left){
    char * result = &(s[right]);
    s[left] = '\0';
    return result;
}
