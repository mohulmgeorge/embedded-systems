#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

enum triState {
    FALSE,
    TRUE,
    ERROR
};

enum triState is_bit_set(int *p, int i);
enum triState set_bit(int *p, int i);
enum triState clear_bit(int *p, int i);
void rm_rightmost_set_bit(int *p);
int pos_rightmost_set_bit(int *p);
bool is_even(int *p);
bool is_power_of_2(int *p);
enum triState toggle_bit(int *p, int i);
bool is_power_of_4(int *p);
bool is_power_of_8(int *p);
bool is_power_of_16(int *p);
int count_set_bits(int *p);

void print_bin(int *p);

int main() {

    int choice, num = 0, i;
    enum triState n;

    while(1) {
        printf("\nMENU\n");
        printf("******\n");
        printf("1. Check if the ith bit is set or not\n");
        printf("2. Set the ith bit of a number\n");
        printf("3. Clear the ith bit of a number\n");
        printf("4. Remove the last set bit of a number\n");
        printf("5. Find the position of rightmost set bit of a number\n");
        printf("6. Find whether a number is even or odd\n");
        printf("7. Check if the number is a power of 2?\n");
        printf("8. Check if the number is a power of 4?\n");
        printf("9. Check if the number is a power of 8?\n");
        printf("10. Check if the number is a power of 16?\n");
        printf("11. Toggle ith Bit of a number\n");
        printf("12. Count the number of set bits in a number\n");
        printf("43. Quit\n");

        printf("Enter option: ");
        scanf("%d",&choice);
        printf("\n");

        switch(choice) {
            case 1:
                printf("1. Check if the ith bit is set or not\n");
                printf("Enter number: ");
                scanf("%d", &num);
                printf("Enter the bit: ");
                scanf("%d", &i);
                printf("Binary format of %d:\n", num);
                print_bin(&num);
                n = is_bit_set(&num, i);
                if(n == ERROR)
                    printf("Invalid bit number!");
                else if(n == FALSE)
                    printf("Bit %d is not set\n", i);
                else if(n == TRUE)
                    printf("Bit %d is set\n", i);
                break;
            case 2:
                printf("2. Set the ith bit of a number\n");
                printf("Enter number: ");
                scanf("%d", &num);
                printf("Enter the bit position: ");
                scanf("%d", &i);
                printf("Before bit set:\n");
                print_bin(&num);
                n = set_bit(&num, i);
                if(n == ERROR)
                    printf("Invalid bit position!");
                else if(n == TRUE) {
                    printf("After bit set:\n");
                    print_bin(&num);
                }
                break;
            case 3:
                printf("3. Clear the ith bit of a number\n");
                printf("Enter number: ");
                scanf("%d", &num);
                printf("Enter the bit position: ");
                scanf("%d", &i);
                printf("Before bit clear:\n", num);
                print_bin(&num);
                n = clear_bit(&num, i);
                if(n == ERROR)
                    printf("Invalid bit position!");
                else if(n == TRUE) {
                    printf("After bit clear:\n");
                    print_bin(&num);
                }
                break;
            case 4:
                printf("4. Remove the last set bit (rightmost bit) of a "\
                    "number\n");
                printf("Enter number: ");
                scanf("%d", &num);
                printf("Enter the bit: ");
                scanf("%d", &i);
                printf("Before:\n");
                print_bin(&num);
                rm_rightmost_set_bit(&num);
                printf("After\n");
                print_bin(&num);               
                break;
            case 5:
                printf("5. Find the position of rightmost set bit of a "\
                    "number\n");
                printf("Enter number: ");
                scanf("%d", &num);
                printf("Binary format of %d:\n", num);
                print_bin(&num);
                printf("The rightmost set bit of %d is in position %d\n", num,\
                     pos_rightmost_set_bit(&num));
                break;
            case 6:
                printf("6. Find whether a number is even or odd\n");
                printf("Enter number: ");
                scanf("%d", &num);
                printf("%d is %s\n", num, is_even(&num)?"even":"odd");
                break;
            case 7:
                printf("7. Check if the number is a power of 2?\n");
                printf("Enter number: ");
                scanf("%d", &num);
                printf("%d is %sa power of 2\n", num, is_power_of_2(&num)?"":"not ");
                break;
            case 8:
                printf("8. Check if the number is a power of 4?\n");
                printf("Enter number: ");
                scanf("%d", &num);
                printf("%d is %sa power of 4\n", num, is_power_of_4(&num)?"":"not ");
                break;
            case 9:
                printf("9. Check if the number is a power of 8?\n");
                printf("Enter number: ");
                scanf("%d", &num);
                printf("%d is %sa power of 8\n", num, is_power_of_8(&num)?"":"not ");
                break;
            case 10:
                printf("10. Check if the number is a power of 16?\n");
                printf("Enter number: ");
                scanf("%d", &num);
                printf("%d is %sa power of 16\n", num, is_power_of_16(&num)?"":"not ");
                break;
            case 11:
                printf("11. Toggle ith Bit of a number\n");
                printf("Enter number: ");
                scanf("%d", &num);
                printf("Enter the bit position: ");
                scanf("%d", &i);
                printf("Before bit toggle:\n", num);
                print_bin(&num);
                n = toggle_bit(&num, i);
                if(n == ERROR)
                    printf("Invalid bit position!");
                else if(n == TRUE) {
                    printf("After bit toggle:\n");
                    print_bin(&num);
                }
                break;
            case 12:
                printf("12. Count the number of set bits in a number\n");
                printf("Enter number: ");
                scanf("%d", &num);
                printf("Binary format of %d:\n", num);
                print_bin(&num);
                printf("There are %d set bits in %d\n", count_set_bits(&num), num);
                break;
            case 43:
                printf("Quit program\n");
                exit(1);
            default:
                printf("Wrong choice!\n");
                break;
        }
    }
}

enum triState is_bit_set(int *p, int i) {
    if(i < 0 || i > 31)
        return ERROR;

    if(*p & (1 << i) != 0 )
        return TRUE;
    return FALSE;
}

void print_bin(int *p) {

    int max = sizeof(int) * 8;

    for(int i=max-1; i>=0; i--) {
        if(*p&(1<<i))
            printf("1");
        else
            printf("0");
        
        if(i%4==0)
            printf(" ");
    }

    printf("\n");
}

enum triState set_bit(int *p, int i) {
    if(i < 0 || i > 31) 
        return ERROR;

    *p = *p|(1<<i);
    return TRUE;
}

enum triState clear_bit(int *p, int i) {

    if(i < 0 || i > 31) 
        return ERROR;

    *p = *p&~(1<<i);
    return TRUE;
}

void rm_rightmost_set_bit(int *p) {
    *p = *p & (*p - 1);
}

int pos_rightmost_set_bit(int *p) {
    return log(*p & ~(*p-1)) / log (2);
}

bool is_even(int *p) {
    if((*p & 1) == 0)
        return true;
    return false;
}

bool is_power_of_4(int *p) {
    if((*p & (*p - 1)) == 0)
        if((*p & 0xAAAAAAAA) == 0)
            return true;
    return false;
}

bool is_power_of_2(int *p) {
    if((*p & (*p - 1)) == 0)
        return true;
    return false;
}

bool is_power_of_8(int *p) {
    if((*p & (*p - 1)) == 0)
        if((*p & 0xB6DB6DB6) == 0)
            return true;
    return false;
}

bool is_power_of_16(int *p) {
    if((*p & (*p - 1)) == 0)
        if((*p & 0xEEEEEEEE) == 0)
            return true;
    return false;
}

enum triState toggle_bit(int *p, int i) {
    if(i < 0 || i > 31) 
        return ERROR;

    *p = *p^(1<<i);
    return TRUE;
}

int count_set_bits(int *p) {
    int n = *p, c = 0;

    while(n != 0) {
        n &= (n - 1);
        c++;
    }

    return c;
}