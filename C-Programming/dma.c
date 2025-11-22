/* Oct 21 Task: Dynamic Memory Allocation */

#include <stdio.h>
#include <stdlib.h>

int *func(int size) {

    int *p;
    p = (int *) malloc(size * sizeof(int));

    if(p == NULL) {
        printf("Memory allocation failed!");
        exit(1);
    }

    return p;

}

int *func2(int size, int* p) {

    p = (int *) realloc(p, size * sizeof(int));

    if(p == NULL) {
        printf("Memory allocation failed!");
        exit(1);
    }

    return p;

}

int main() {

    int *p,n;

    printf("Enter the number of integers to be stored: ");
    scanf("%d", &n);
    
    p = func(n);

    for(int i=0; i<n; i++) {
        printf("Enter integer %d: ",i+1);
        scanf("%d", p+i);
    }

    printf("\nInitial array: \n");
    for(int i=0; i<n; i++) {
        printf("%d\n", *(p+i));
    }

    /*Allocate memory for 5 more integers*/
    p = func2(n+5,p);

    printf("\n");

    for(int i=n; i<n+5; i++) {
        printf("Enter integer %d: ",i+1);
        scanf("%d", p+i);
    }

    printf("\nFinal array: \n");
    for(int i=0; i<n+5; i++) {
        printf("%d\n", *(p+i));
    }

    free(p);

    return 0;
}