#include <stdio.h>
#include <stdlib.h>

struct node {
    int n;
    struct node *link;
};

void display(struct node *start);
void count(struct node *start);
void search(struct node *start, int item);
struct node *ins_beg(struct node *start, int data);
struct node *ins_end(struct node *start, int data);
struct node *ins_after(struct node *start, int data, int val);
struct node *ins_before(struct node *start, int data, int val);
struct node *ins_at_pos(struct node *start, int data, int pos);
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
        p = p->link;
    }
    printf("\n");

}

void count(struct node *start) {
    struct node * p;
    int count = 0;

    if(start == NULL) {
        printf("List is empty!\n");
        return;
    }

    p = start;

    while(p != NULL) {
        count++;
        p = p->link;
    }

    printf("Number of elements in the list are %d\n",count);

}

void search(struct node *start, int item) {
    struct node *p;
    int pos = 1;

    if(start == NULL) {
        printf("List is empty!\n");
        return;
    }

    p = start;

    while(p != NULL) {
        if( p->n == item) {
            printf("Item %d found at position %d\n",item,pos);
            return;
        }
        p = p->link;
        pos++;
    }

    printf("Item %d not found in list\n",item);

}

struct node *ins_beg(struct node *start, int data) {
    struct node *n;
    
    n = (struct node *) malloc(sizeof(struct node));

    n->n = data;
    n->link = start;
    start = n;

    return start;
}

struct node *ins_end(struct node *start, int data) {
    struct node *n, *p;

    n = (struct node *) malloc(sizeof(struct node));
    p = start;

    while(p->link != NULL)
        p = p->link;
    
    n->n = data;
    n->link = NULL;
    p->link = n;

    return start;
}

struct node *ins_after(struct node *start, int data, int val) {
    struct node *n, *p;
    int c = 1;

    p = start;

    while (p != NULL) {
        if(p->n == val) {
            n = (struct node *) malloc(sizeof(struct node));
            n->n = data;
            n->link = p->link;
            p->link = n;

            return start;
        }
        p = p->link;
    }

    printf("%d is not present in the list!\n", val);

    return start;
}

struct node *ins_before(struct node *start, int data, int val) {
    struct node *n, *p;
    
    if(start == NULL) {
        printf("List is empty!\n");
        return start;
    }

    if(start->n == data) {
        n = (struct node *) malloc(sizeof(struct node));
        n->n = data;
        n->link = start;
        start = n;
        return start;
    }

    p = start;

    while (p->link != NULL) {

        if(p->link->n == val) {
            n = (struct node *) malloc(sizeof(struct node));
            n->n = data;
            n->link = p->link;
            p->link = n;

            return start;
        }
        p = p->link;
    }

    printf("%d is not present in the list!\n",val);
    return start;
}

struct node *ins_at_pos(struct node *start, int data, int pos) {

    struct node *n, *p;
    int count;

    if(pos == 1) {
        n = (struct node *) malloc(sizeof(struct node));
        n->n = data;
        n->link = start;
        start = n;
        return start;
    }

    count = 2;
    p = start;

    while(p != NULL) {
        if(count == pos) {
            n = (struct node *) malloc(sizeof(struct node));
            n->n = data;
            n->link = p->link;
            p->link = n;

            return start;
        }

        p = p->link;
        count++;
    }

    printf("%d position is not present in the list!\n", pos);    
    return start;
}

struct node *create_list(struct node *start) {
    int n, data;

    printf("Enter number of nodes: ");
    scanf("%d",&n);

    start = NULL;
    if(n==0) {
        return start;
    }
    printf("Enter the data to be entered: ");
    scanf("%d",&data);
    start = ins_beg(start, data);

    for(int i=2; i<=n; i++) {
        printf("Enter the data to be entered: ");
        scanf("%d",&data);
        start = ins_end(start, data);
    }

    return start;
}

struct node *del(struct node *start, int data) {
    struct node *p, *tmp;

    if(start == NULL) {
        printf("List is empty!\n");
        return start;
    }

    if(start->n == data) {
        tmp = start;
        start = start->link;
        free(tmp);
        return start;
    }

    p = start;

    while(p->link != NULL) {
        if(p->link->n == data) {
            tmp = p->link;
            p->link = tmp->link;
            free(tmp);
            return start;
        }
        p = p->link;
    }

    printf("Element %d is not found in list!\n",data);
    return start;
}

struct node *reverse(struct node *start) {
    struct node *prev, *p, *next;

    prev = NULL;
    p = start;

    while(p != NULL) {
        next = p->link;
        p->link = prev;
        prev = p;
        p = next;
    }

    start = prev;
    return start;
}