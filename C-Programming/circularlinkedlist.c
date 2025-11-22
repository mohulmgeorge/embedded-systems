#include <stdio.h>
#include<stdlib.h>

struct node {
    int n;
    struct node *link;
};

void display(struct node *last);
void count(struct node *last);
void search(struct node *last, int item);
struct node *ins_beg(struct node *last, int data);
struct node *ins_end(struct node *last, int data);
struct node *ins_after(struct node *last, int data, int val);
struct node *ins_before(struct node *last, int data, int val);
struct node *ins_at_pos(struct node *last, int data, int pos);
struct node *create_list(struct node *last);
struct node *del(struct node *last, int data);
struct node *reverse(struct node *last);

int main() {

    struct node *last = NULL;
    int choice, data, pos, item;

    while(1) {

        printf("\nMENU\n");
        printf("******\n");
        printf("1. Create List\n");
        printf("2. Display List\n");
        printf("3. Count\n");
        printf("4. Search\n");
        printf("5. Insert to empty list / insert at beginning\n");
        printf("6. Insert at end\n");
        printf("7. Insert after\n");
        printf("8. Insert before\n");
        printf("9. Insert at position\n");
        printf("10. Delete\n");
        printf("11. Reverse List\n");
        printf("12. Quit\n");

        printf("Enter option: ");
        scanf("%d",&choice);
        printf("\n");

        switch(choice) {
            case 1:
                last = create_list(last);
                break;
            case 2:
                display(last);
                break;
/*            case 3:
                count(last);
                break;
            case 4:
                printf("Enter the data to be searched: ");
                scanf("%d", &data);
                search(last, data);
                break;
            case 5:
                printf("Enter the data to be inserted: ");
                scanf("%d", &data);
                last = ins_beg(last, data);
                break;
            case 6:
                printf("Enter the data to be inserted: ");
                scanf("%d", &data);
                last = ins_end(last, data);
                break;
            case 7:
                printf("Enter the data to be inserted: ");
                scanf("%d", &data);
                printf("Enter the element after which to insert: ");
                scanf("%d", &item);
                last = ins_after(last, data, item);
                break;
            case 8:
                printf("Enter the data to be inserted: ");
                scanf("%d", &data);
                printf("Enter the element before which to insert: ");
                scanf("%d", &item);
                last = ins_before(last, data, item);
                break;
            case 9:
                printf("Enter the data to be inserted: ");
                scanf("%d", &data);
                printf("Enter the postion at which to insert: ");
                scanf("%d", &pos);
                last = ins_at_pos(last, data, pos);
                break;
            case 10:
                printf("Enter the data to be deleted: ");
                scanf("%d", &data);
                last = del(last, data);
                break;
            case 11:
                last = reverse(last);
                break;
*/          case 12:
                printf("Quit program\n");
                exit(1);
            default:
                printf("Wrong choice!\n");
        }
    }

    return 0;
}

struct node *ins_beg(struct node *last, int data) {

    struct node *p;

    p = (struct node *) malloc(sizeof(struct node));
    p->n = data;
    
    if(last == NULL) {
        last = p;
        last->link = last;
        return last; 
    }
/*
    if(last->link == last) {
        last->link = p;
        p->link = last;
        return last;
    }
*/
    p->link = last->link;
    last->link = p;
    
    return last;
}

struct node *create_list(struct node *last) {
    int n, data;

    printf("Enter number of nodes: ");
    scanf("%d",&n);

    last = NULL;
    if(n==0) {
        return last;
    }
    printf("Enter the data to be entered: ");
    scanf("%d",&data);
    last = ins_beg(last, data);

    for(int i=2; i<=n; i++) {
        printf("Enter the data to be entered: ");
        scanf("%d",&data);
        last = ins_end(last, data);
    }

    return last;
}

struct node *ins_end(struct node *last, int data) {

    struct node *p;

    p = (struct node *) malloc(sizeof(struct node));
    p->n = data;

    if(last == NULL) {
        last = p;
        last->link = last;
        return last; 
    }
/*
    if(last->link == last) {
        p->link = last->link;
        last->link = p;
        last = p;
        return last;
    }
*/    
    p->link = last->link;
    last->link = p;
    last = p;

    return last;
}

void display(struct node *last) {

    struct node* p;

    if(last == NULL) {
        printf("List is empty!\n");
        return;
    }

    p = last->link;

    printf("List is: \n");
    do {
        printf("%d ",p->n);
        p = p->link;
    } while(p!= last->link);
    printf("\n");

}