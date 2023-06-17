// add 4 numbers using functions

#include <stdio.h>

int add4(int a, int b, int c, int d);
int add2(int x, int y);

int main(void) {
    int result = add4(5, 7, 10, 23);
    printf("%d\n", result);
    return 0;
}

int add4(int a, int b, int c, int d) {
    int res1 = add2(a, b);
    int res2 = add2(c, d);
    return add2(res1, res2);
}

int add2(int x, int y) {
    return x + y;
}