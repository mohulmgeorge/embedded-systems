#include <stdio.h>

int add(int x, int y) {
   return x+y; 
}

int subtract(int x, int y) {
    return x-y;
}

int multiply(int x, int y) {
    return x*y;
}

float divide(int x, int y) {
    /*since both x and y are integers, x/y performs integer division.so we have 
    to typecast one operand to float*/
    return (float)x/y;  
}

void main() {
    int a,b;
    printf("Enter value of a: ");
    scanf("%d",&a);
    printf("Enter value of b: ");
    scanf("%d",&b);
    
    printf("a + b = %d\n", add(a,b));
    printf("a - b = %d\n", subtract(a,b));
    printf("a * b = %d\n", multiply(a,b));
    printf("a / b = %.2f\n", divide(a,b));

}