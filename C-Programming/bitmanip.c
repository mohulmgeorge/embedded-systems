/*Program to understand bit manipulation*/
#include <stdio.h>
#include <stdlib.h>

void printBin(int *p);
void setBit(int *p);
void clearBit(int *p);
void toggleBit(int *p);
void swapNumbers();

int main() {

    int n, *ptr, choice;

    printf("Enter an integer: ");
    scanf("%d",&n);

    ptr = &n;

    while(1) {

        printf("\nMENU\n");
        printf("******\n");
        printf("1. Display binary format\n");
        printf("2. Set bit\n");
        printf("3. Clear bit\n");
        printf("4. Toggle bit\n");
        printf("5. Swap numbers\n");
        printf("6. Quit\n");

        printf("Enter option: ");
        scanf("%d",&choice);
        printf("\n");

        switch(choice) {
            case 1:
                printBin(ptr);;
                break;
            case 2:
                setBit(ptr);;
                break;
            case 3:
                clearBit(ptr);;
                break;
            case 4:
                toggleBit(ptr);;
                break;
            case 5:
                swapNumbers();;
                break;
            case 6:
                printf("Quit program\n");
                exit(1);
            default:
                printf("Wrong choice!\n");
        }
    }
    
    return 0;
}

void printBin(int *p) {

    int max = sizeof(int) * 8;

    for(int i=max-1; i>=0; i--) {
        if(*p&(1<<i))
            printf("1");
        else
            printf("0");
        
        if(i%4==0)
            printf(" ");
    }

    printf("\n");
}

void setBit(int *p) {

    int pos;

    printf("Enter the bit position: \n");
    scanf("%d",&pos);

    if(pos < 1 || pos > 32) {
        printf("Invalid bit position!\n");
        return;
    }

    *p = *p|(1<<pos-1);

    printBin(p);
}

void clearBit(int *p) {

    int pos;

    printf("Enter the bit position: \n");
    scanf("%d",&pos);

    if(pos < 1 || pos > 32) {
        printf("Invalid bit position!\n");
        return;
    }

    *p = *p&~(1<<pos-1);

    printBin(p);
}

void toggleBit(int *p) {

    int pos;

    printf("Enter the bit position: \n");
    scanf("%d",&pos);

    if(pos < 1 || pos > 32) {
        printf("Invalid bit position!\n");
        return;
    }

    *p = *p^(1<<pos-1);

    printBin(p);
}

//Swap numbers without using temp variable using bit manipulation
void swapNumbers() {
    int a, b;

    printf("Enter first integer: ");
    scanf("%d",&a);

    printf("Enter second integer: ");
    scanf("%d",&b);

    printf("Before swap: a = %d, b = %d\n",a,b);

    a = a ^ b;
    b = a ^ b;
    a = a ^ b;

    printf("After swap: a = %d, b = %d\n",a,b);
}