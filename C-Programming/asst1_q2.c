#include<stdio.h>

void printBin(char *p);
void setBit(char *p, int n);
void clearBit(char *p, int n);
void toggleBit(char *p, int n);

int main() {

    char n, *ptr;
    int choice;

    printf("Enter an 8-bit unsigned character: ");
    scanf("%d",&n);

    ptr = &n;

    printf("The binary format of the 8-bit unsigned character is:\n");
    printBin(ptr);

    printf("Set the 3rd bit\n");
    setBit(ptr, 3);
    printf("Clear the 6th bit\n");
    clearBit(ptr, 6);
    printf("Toggle the 1st bit\n");
    toggleBit(ptr, 1);

    return 0;
}

void printBin(char *p) {

    int max = sizeof(char) * 8;

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

void setBit(char *p, int n) {

    if(n < 1 || n > 8) {
        printf("Invalid bit position!\n");
        return;
    }

    *p = *p|(1<<n-1);

    printBin(p);
}

void clearBit(char *p, int n) {

    if(n < 1 || n > 8) {
        printf("Invalid bit position!\n");
        return;
    }

    *p = *p&~(1<<n-1);

    printBin(p);
}

void toggleBit(char *p, int n) {

    if(n < 1 || n > 8) {
        printf("Invalid bit position!\n");
        return;
    }

    *p = *p^(1<<n-1);

    printBin(p);
}