/*Program to multiply two matrices*/
#include <stdio.h>

#define R1 2
#define C1 2
#define R2 C1
#define C2 3

int main() {

    int mat1[R1][C1], mat2[R2][C2], mat3[R1][C2];

    printf("Enter the elements of matrix 1(%dx%d) row-wise: \n",R1,C1);
    for(int i=0; i<R1; i++)
        for(int j=0; j<C1; j++)
            scanf("%d",&mat1[i][j]);

    printf("Enter the elements of matrix 2(%dx%d) row-wise: \n",R2,C2);
    for(int i=0; i<R2; i++)
        for(int j=0; j<C2; j++)
            scanf("%d",&mat2[i][j]);

    for(int i=0; i<R1; i++)
        for(int j=0; j<C2; j++) {
            mat3[i][j] = 0;
            for(int k=0; k<C1; k++) 
                mat3[i][j] += mat1[i][k] * mat2[k][j];            
        }

    printf("Elements of matrix 1(%dx%d): \n",R1,C1);
    for(int i=0; i<R1; i++) {
        for(int j=0; j<C1; j++)
            printf("%d\t",mat1[i][j]);
        printf("\n");
    }

    printf("Elements of matrix 2(%dx%d): \n",R2,C2);
    for(int i=0; i<R2; i++) {
        for(int j=0; j<C2; j++)
            printf("%d\t",mat2[i][j]);
        printf("\n");
    }
    
    printf("Product of the above two matrices: \n");
    for(int i=0; i<R1; i++) {
        for(int j=0; j<C2; j++)
            printf("%d\t",mat3[i][j]);
        printf("\n");
    }

    return 0;

}