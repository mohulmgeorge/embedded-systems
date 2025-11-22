#include <stdio.h>
#include <stdlib.h>

struct node {
    int n;
    struct node *link;
};

void display(struct node *p);

int main() {

    struct node *start = NULL;
    int choice;

    while(1) {

        printf("\nMENU\n");
        printf("******\n");
        printf("1. Display List\n");
        printf("12. Quit\n");

        printf("Enter option: ");
        scanf("%d",&choice);
        printf("\n");

        switch(choice) {
            case 1:
                display(start);
                break;
            case 12:
                printf("Quit program\n");
                exit(1);
            default:
                printf("Wrong choice!\n");
        }
    }

    return 0;

}

void display(struct node *start) {

    struct node *p;

    if(start == NULL) {
        printf("List is empty!\n");
        return;
    }

    p = start;

    printf("List is: \n");
    while (p!=NULL) {
        printf("%d ",p->n);
        p = p->link;
    }
    printf("\n");

}