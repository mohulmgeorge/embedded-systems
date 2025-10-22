/* Calculator program where user chooses the operator and only that operation
will be performed */
#include <stdio.h>
#include <stdlib.h>

int main() {

    float a,b;
    char op;

    printf("Simple Calculator\n");
    printf("*******************\n");
    
    printf("Enter first number: ");
    scanf("%f",&a);

    printf("Enter operator (+,-,*,/): ");
    scanf(" %c",&op);

    printf("Enter second number: ");
    scanf("%f",&b);

    switch (op)
    {
    case '+':
        printf("%.2f + %.2f = %.2f\n",a,b,a+b);
        break;

    case '-':
        printf("%.2f - %.2f = %.2f\n",a,b,a-b);
        break;

    case '*':
        printf("%.2f * %.2f = %.2f\n",a,b,a*b);
        break;

    case '/':
        if(b == 0) {
            printf("Cannot divide by 0!");
            exit(1);
        }
        printf("%.2f / %.2f = %.2f\n",a,b,a/b);
        break;    

    default:
        printf("Invalid operator!\n");
        break;
    }

    return 0;

}