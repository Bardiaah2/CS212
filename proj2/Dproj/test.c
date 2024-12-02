#include <stdio.h>
#include <stdlib.h>

int main(){
    char *a = "b";
    char *b = "b";
    char *c = "0";
    int a_int = (int) *a;
    int b_int = (int) *b;
    int c_int = (int) *c;
    int a_ascii = atoi(a);
    printf("force int way a: %d\n", a_int);
    printf("force int way b: %d\n", b_int);
    printf("force int way 0: %d\n", c_int);
    printf("ascii buit-in function: %d\n", a_ascii);
    printf("\n");
    printf("%f\n", 1 + 0.1);

}
