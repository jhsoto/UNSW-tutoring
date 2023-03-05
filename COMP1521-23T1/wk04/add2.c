// Sum 2 numbers using functions

#include <stdio.h>

int add2(int x, int y);

int main(void) {
    int result = add2(5, 7);
    printf("%d\n", result);
    return 0;
}

int add2(int x, int y) {
    return x + y;
}