#include <stdio.h>
#include <stdlib.h>

int main(){
    int b = 2;
    int *a = &b;


    (*a)++;
    printf("%d\n", *a);

    printf("%d\n", b);
    
    b++;

    printf("%d\n", *a);
    printf("%d\n", b);
    
    return 0;
}
