#include <stdio.h>

int main (){
    int *A = 0x8000;
    int *B[3] = {A, A+7, A+14};
    
    printf("%d\n", *(A+5) - *(A+3));
    printf("%d\n", (A+7) - (A+2));
    printf("%d\n", A[5] - *(A+4));

}
