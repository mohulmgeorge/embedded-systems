/*Create a program that allows users to add, remove, and view items on a shopping list using a linked list.
Enhance it by adding features like marking items as purchased*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ITEM_SIZE 50
#define CHECK 1
#define UNCHECK 0

struct node {
    char item[ITEM_SIZE];
    int flag:1;
    struct node *link;
};

void display(struct node *start);
int count(struct node *start);

struct node *ins_beg(struct node *start, char *s);
struct node *ins_end(struct node *start, char *s);
struct node *create_list(struct node *start);
struct node *del(struct node *start, char *s);
void mark(struct node* start, char *s);

int main() {

    struct node *start = NULL;
    int choice, data, pos;
    char item[ITEM_SIZE];

    while(1) {

        printf("\nSHOPPING LIST\n");
        printf("***************\n");
        printf("1. Create List\n");
        printf("2. View List\n");
        printf("3. Add Item\n");
        printf("4. Remove Item\n");
        printf("5. Mark purchased\n");
        printf("6. Quit\n");

        printf("Enter option: ");
        scanf("%d", &choice);
        printf("\n");

        switch(choice) {
            case 1:
                start = create_list(start);
                break;
            case 2:
                display(start);
                break;
            case 3:
                printf("Enter item name: ");
                scanf("%s", item);
                start = ins_beg(start, item);
                break;
            case 4:
                printf("Enter item to be deleted: ");
                scanf("%s", &item);
                start = del(start, item);
                break;
            case 5:
                printf("Enter item to be marked: ");
                scanf("%s", &item);
                mark(start, item);
                break;
            case 6:
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

    //c = count(start);

    p = start;

    printf("Your shopping list is: \n");
    while (p!=NULL) {
        printf("[%c] %s\n", p->flag?'X':' ', p->item);
        p = p->link;
    }
    printf("\n");

}

int count(struct node *start) {
    struct node * p;
    int count = 0;

    if(start == NULL) {
        printf("List is empty!\n");
        return -1;
    }

    p = start;

    while(p != NULL) {
        count++;
        p = p->link;
    }

    return count;

}

struct node *ins_beg(struct node *start, char *s) {
    struct node *n;
    
    n = (struct node *) malloc(sizeof(struct node));

    n->flag = UNCHECK;
    strcpy(n->item,s);
    n->link = start;
    start = n;

    return start;
}

struct node *ins_end(struct node *start, char *s) {
    struct node *n, *p;

    n = (struct node *) malloc(sizeof(struct node));
    p = start;

    while(p->link != NULL)
        p = p->link;
    
    n->flag = UNCHECK;
    strcpy(n->item,s);
    n->link = NULL;
    p->link = n;

    return start;
}

struct node *create_list(struct node *start) {
    int n;
    char item[ITEM_SIZE];

    printf("Enter number of items: ");
    scanf("%d",&n);

    start = NULL;
    if(n<=0) {
        return start;
    }
    printf("Enter item name: ");
    scanf("%s",item);
    start = ins_beg(start, item);

    for(int i=2; i<=n; i++) {
        printf("Enter item name: ");
        scanf("%s",item);
        start = ins_end(start, item);
    }

    return start;
}

struct node *del(struct node *start, char *s) {
    struct node *p, *tmp;

    if(start == NULL) {
        printf("List is empty!\n");
        return start;
    }

    if(strcmp(s,start->item) == 0) {
        tmp = start;
        start = start->link;
        free(tmp);
        return start;
    }

    p = start;

    while(p->link != NULL) {
        if(strcmp(p->link->item,s) == 0) {
            tmp = p->link;
            p->link = tmp->link;
            free(tmp);
            return start;
        }
        p = p->link;
    }

    printf("'%s' is not found in list!\n", s);
    return start;

}


void mark(struct node* start, char *s) {

    struct node *p;

    if(start == NULL) {
        printf("List is empty!\n");
        return;
    }

    p = start;

    while(p != NULL) {
        if( strcmp(p->item,s) == 0) {
            p->flag = CHECK;
            return;
        }
        p = p->link;
    }

    printf("Item '%s' not found in list\n", s);
}