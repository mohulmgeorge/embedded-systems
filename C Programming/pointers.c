#include <stdio.h>

void main(){

    
    int arr[5] = {1,2,3,4,5};
    int *arrPtr = arr, x;
    
    /*Oct 18 Task 1: Increment all lements of array by 5 using a single pointer*/
    printf("Initial array elements: ");

    for (char i = 0; i < 5; i++)
    {
        printf("%d ",*(arrPtr+i)); //1 2 3 4 5
    }
    
    printf("\n");

    for (char i = 0; i < 5; i++)
    {
        *(arrPtr+i) = *(arrPtr+i) + 5;
    }

    printf("Final array elements: ");

    for (char i = 0; i < 5; i++)
    {
        printf("%d ",*(arrPtr+i)); //6 7 8 9 10
    }

    printf("\n");

    /*Oct 18 Task 2: Pointer Arithmetic*/
    x = *arrPtr++;  //ie, x = *arrPtr; arrPtr = arrPtr + 1; post-increment operator
    printf("Value of arrPtr = %d\n",*arrPtr);
    printf("Value of x = %d\n",x);

    x = *++arrPtr;  //ie, arrPtr = arrPtr + 1;  x = *arrPtr; pre-increment operator
    printf("Value of arrPtr = %d\n",*arrPtr);
    printf("Value of x = %d\n",x);

    x = ++*arrPtr;  //ie, *arrPtr = *arrPtr + 1;  x = *arrPtr; pre-increment operator
    printf("Value of arrPtr = %d\n",*arrPtr);
    printf("Value of x = %d\n",x);

    x = (*arrPtr)++;  //ie, x = *arrPtr; *arrPtr = *arrPtr + 1;  post-increment operator
    printf("Value of arrPtr = %d\n",*arrPtr);
    printf("Value of x = %d\n",x);    

    arrPtr = arr;

    printf("New array elements: ");

    for (char i = 0; i < 5; i++)
    {
        printf("%d ",*(arrPtr+i)); //6 7 10 9 10
    }

    printf("\n");

    /*Oct 18 Task 3 (HW): Pointer Arithmetic (use --)*/
    arrPtr = arr+4;
    x = *arrPtr--;  //ie, x = *arrPtr; arrPtr = arrPtr - 1; post-decrement operator
    printf("Value of arrPtr = %d\n",*arrPtr);
    printf("Value of x = %d\n",x);

    x = *--arrPtr;  //ie, arrPtr = arrPtr - 1;  x = *arrPtr; pre-decrement operator
    printf("Value of arrPtr = %d\n",*arrPtr);
    printf("Value of x = %d\n",x);

    x = --*arrPtr;  //ie, *arrPtr = *arrPtr - 1;  x = *arrPtr; pre-decrement operator
    printf("Value of arrPtr = %d\n",*arrPtr);
    printf("Value of x = %d\n",x);

    x = (*arrPtr)--;  //ie, x = *arrPtr; *arrPtr = *arrPtr - 1;  post-decrement operator
    printf("Value of arrPtr = %d\n",*arrPtr);
    printf("Value of x = %d\n",x);

    arrPtr = arr;

    printf("New array elements: ");

    for (char i = 0; i < 5; i++)
    {
        printf("%d ",*(arrPtr+i)); //6 7 8 9 10
    }

    printf("\n");

}