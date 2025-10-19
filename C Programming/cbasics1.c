#include <stdio.h>

void main() {

    int i = 5;
    char c = 'a';
    long int li = 123456789;

    printf("Integer: %-d %i\n", i, i);
    printf("Character: %c\n", c);
    printf("Long Integer: %li\n", li);

    printf("Size of integer: %d\n", sizeof(i));
    printf("Size of character: %d\n", sizeof(c));
    printf("Size of long integer: %d\n", sizeof(li));
    
}