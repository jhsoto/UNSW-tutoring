// Calculates a factorial recursively
#include <stdio.h>
#include <stdlib.h>

int factorial(n);

int main(int argc, char *argv[]) {
    // TODO: Extract n from the command line arguments
    int n = 42;

    int result = factorial(n);
    printf("%d! = %d\n", n, result);

    return 0;
}

int factorial(n) {
    // TODO
    return 1;
}