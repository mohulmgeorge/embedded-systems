// 1) Take a number as input from the user and set the 5th bit to 1.
// 2) Write a code to print the total number of set bit and 0 bit in a number.

#include <stdio.h>

void displayBin(int *p);
void setBit(int *p, int k);
void toggleBit(int *p, int k);
void printCount(int *p);

int main() {

    int n, k;

    printf("Enter a number: ");
    scanf("%d", &n);

    printf("Before bit manipulation: ");
    displayBin(&n);
    printf("\n");

    printCount(&n);

    printf("Enter bit to set: ");
    scanf("%d", &k);
    setBit(&n, k);

    printf("After bit manipulation: ");
    displayBin(&n);
    printf("\n");

    printCount(&n);

    printf("Enter bit to toggle: ");
    scanf("%d", &k);
    toggleBit(&n, k);

    printf("After toggle: ");
    displayBin(&n);
    printf("\n");

    printCount(&n);

    return 0;
}

void setBit(int *p, int k) {
    *p = *p | (1 << k);
}

void displayBin(int *p) {
    int n = sizeof(int) * 8;

    for(int i = n-1; i >= 0; i--) {
        if(*p&(1<<i))
            printf("1");
        else
            printf("0");
        if(i % 4 == 0)
            printf(" ");
    }
}

void printCount(int *p) {

    int a = 0, b = 0, n = sizeof(int) * 8;

    for(int i = n-1; i >= 0; i--) {
        if(*p&(1<<i))
            a++;
        else
            b++;      
    }

    printf("Total number of set bits = %d\n", a);
    printf("Total number of 0 bits = %d\n", b);
}

void toggleBit(int *p, int k) {
    *p = *p ^ (1 << k);
}