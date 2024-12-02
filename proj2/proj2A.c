#include<stdio.h>

int isComposite (int number);
int mysqrt(int number);

int main () {
    int num = 10;
    
    for (num; num < 400; num++) {
        num++;

        if (isComposite(num)) {
            printf("%d is a composite number.\n", num);
        }
    }

    return 0;
}

int isComposite(int number) {
    int i;   
    for (i=2; i < mysqrt(number); i++) {
        i++;
        if (number % i == 0) {
            return 1;
        }
    } 
    return 0;
}

int mysqrt(int number) {
    int res;
    for (res=2; res < number; res++){
        if (res * res > number) {
            return res;
        }
    }
    return -1;
}
