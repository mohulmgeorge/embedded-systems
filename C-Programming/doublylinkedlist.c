#include <stdio.h>
#include <stdlib.h>

struct node {
    int n;
    struct node *prev;
    struct node *next;
};

void display(struct node *start);
//void count(struct node *start);
//void search(struct node *start, int item);
struct node *ins_beg(struct node *start, int data);
struct node *ins_end(struct node *start, int data);
struct node *ins_after(struct node *start, int data, int val);
struct node *ins_before(struct node *start, int data, int val);
//struct node *ins_at_pos(struct node *start, int data, int pos);
struct node *create_list(struct node *start);
struct node *del(struct node *start, int data);
struct node *reverse(struct node *start);

int main() {

    struct node *start = NULL;
    int choice, data, pos, item;

    while(1) {

        printf("\nMENU\n");
        printf("******\n");
        printf("1. Create List\n");
        printf("2. Display List\n");
        //printf("3. Count\n");
        //printf("4. Search\n");
        printf("5. Insert to empty list / insert at beginning\n");
        printf("6. Insert at end\n");
        printf("7. Insert after\n");
        printf("8. Insert before\n");
        //printf("9. Insert at position\n");
        printf("10. Delete\n");
        printf("11. Reverse List\n");
        printf("12. Quit\n");

        printf("Enter option: ");
        scanf("%d",&choice);
        printf("\n");

        switch(choice) {
            case 1:
                start = create_list(start);
                break;
            case 2:
                display(start);
                break;
            case 3:
                count(start);
                break;
            case 4:
                printf("Enter the data to be searched: ");
                scanf("%d", &data);
                search(start, data);
                break;
            case 5:
                printf("Enter the data to be inserted: ");
                scanf("%d", &data);
                start = ins_beg(start, data);
                break;
            case 6:
                printf("Enter the data to be inserted: ");
                scanf("%d", &data);
                start = ins_end(start, data);
                break;
            case 7:
                printf("Enter the data to be inserted: ");
                scanf("%d", &data);
                printf("Enter the element after which to insert: ");
                scanf("%d", &item);
                start = ins_after(start, data, item);
                break;
            case 8:
                printf("Enter the data to be inserted: ");
                scanf("%d", &data);
                printf("Enter the element before which to insert: ");
                scanf("%d", &item);
                start = ins_before(start, data, item);
                break;
            case 9:
                printf("Enter the data to be inserted: ");
                scanf("%d", &data);
                printf("Enter the postion at which to insert: ");
                scanf("%d", &pos);
                start = ins_at_pos(start, data, pos);
                break;
            case 10:
                printf("Enter the data to be deleted: ");
                scanf("%d", &data);
                start = del(start, data);
                break;
            case 11:
                start = reverse(start);
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
        p = p->next;
    }
    printf("\n");

}