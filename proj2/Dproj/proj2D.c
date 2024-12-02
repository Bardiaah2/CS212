#include <stdio.h>
#include <stdlib.h>

typedef enum
{
   ADD,
   MULT,
   SUBTRACT,
   DIV,
   UNSUPPORTED
} MathOperation;

void IssueBadNumberError()
{
    printf("The string does not represent a floating point number.\n");
    exit(EXIT_FAILURE);
}
void IssueBadOperationError()
{
    printf("The string does not represent a valid operation.\n");
    exit(EXIT_FAILURE);
}

MathOperation GetOperation(char *op)
{
    /* Implement me! */
    if (op[1] != '\0'){
        IssueBadOperationError();
    }
    MathOperation opcode;
    if (*op == 'x'){
        opcode = MULT;
    } else if (*op == '+'){
        opcode = ADD;
    } else if (*op == '/'){
        opcode = DIV;
    } else if (*op == '-'){
        opcode = SUBTRACT;
    } else {
        opcode = UNSUPPORTED;
        IssueBadOperationError();
        }
    return opcode;
}

int CharToInt(char *str){
    int str_int = (int) *str;
    return (str_int - 48);
}

double StringToDouble(char *str)
{
    /* Implement me! */
    double result = 0;
    double decimal = 10.0;
    // the end == '\0'
    int i = 0;
    while (str[i] != '\0'){
        // check if it's "."
        if (str[i] == '.') {
            if (decimal < 1){
                IssueBadNumberError();
            }
            decimal = 0.1;
            i++;
            continue;
        }
        if (str[i] == '-'){
            if (i != 0){
                IssueBadNumberError();
            }
            i++;
            continue;
        }

        // make a int
        int num = CharToInt(&str[i]);
        // if int is less than 0 or more than 9 throw error
        if ((num < 0) || (num > 9)){
            IssueBadNumberError();
        }

        if (decimal > 1){
            result = result * decimal + num;
        } else {
            result = result + num * decimal;
            decimal = decimal / 10;
        }

        i++;
    }
    if (str[0] == '-'){
        result = -result;
    }
    return result;

}


int main(int argc, char *argv[])
{
    double v = StringToDouble(argv[1]);
    MathOperation op = GetOperation(argv[2]);
    double v2 = StringToDouble(argv[3]);
    double result = 0.;
    switch (op)
    {
       case ADD:
         result = v+v2;
         break;
       case MULT:
         result = v * v2;
         break;
       case SUBTRACT:
         result = v - v2;
         break;
       case DIV:
         result = v / v2;
         break;
    }
    printf("%d\n", (int) result);
 
    return 0;
}
