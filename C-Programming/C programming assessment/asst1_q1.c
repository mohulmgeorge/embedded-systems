#include <stdio.h>
#include <stdlib.h>

int second_largest(int *arr, int n);

int main() {

    int *arr, n, a=0;

    printf("Enter size of array (at least 2): ");
    scanf("%d", &n);

    if(n < 2)
        exit(1);

    arr = (int *) malloc(sizeof(int) * n);

    for(int i=0; i<n; i++) {
        printf("Enter integer %d: ", i+1);
        scanf("%d", arr+i);
    }
    printf("\n");

    printf("The entered array is: \n");
    for(int i=0; i<n; i++) {
        printf("%d\t", *(arr+i));
    }
    printf("\n\n");

    printf("The second largest element in the array is %d\n", second_largest(arr, n));

    free(arr);

    return 0;
}

int second_largest(int *arr, int n) {
    int l1 = 0, l2 = 0;

    if(*(arr) > *(arr + 1)) {
        l1 = *(arr);
        l2 = *(arr + 1);
    }
    else {
        l2 = *(arr);
        l1 = *(arr + 1);
    }

    for(int i = 2; i < n; i++) {
        if(*(arr+i) > l1) {
            l2 = l1;
            l1 = *(arr+i);
        }
        else if(*(arr+i) > l2) {
            l2 = *(arr+i);
        }
    }

    return l2;
}