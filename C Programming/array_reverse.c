/*Program to reverse an array*/
#include <stdio.h>

#define SIZE 5

int main() {

    int arr[SIZE] = {1,2,3,4,5}, tmp;

    printf("Initial array: ");
    for(int i=0; i<SIZE; i++) {
        printf("%d\t",arr[i]);
    }
    printf("\n");

    for (int i=0, j=SIZE-1; i<=SIZE/2 ; i++, j--) {
        tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }

    printf("Reversed array: ");
    for(int i=0; i<SIZE; i++) {
        printf("%d\t",arr[i]);
    }
    printf("\n");

    return 0;

}