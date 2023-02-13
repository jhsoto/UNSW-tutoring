// Calculates a factorial recursively
#include <stdio.h>
#include <stdlib.h>

int factorial(int n);

int main(int argc, char *argv[]) {
    // argc - number of command line arguments given
    //        Note: the name of the program (eg. "./factorial") counts!
    // argv - an array of strings, each string is one of the command line arguments
    
    // Here we check we have been given the expected number of arguments
    if (argc != 2) {
        printf("Usage: %s <n>", argv[0]);
    }
    // atoi converts a string of a number (like "10") into the number itself
    int n = atoi(argv[1]);

    int result = factorial(n);
    printf("%d! = %d\n", n, result);

    return 0;
}

// Note: We are assuming that n is not negative!
int factorial(int n) {
    // Base case: 0! = 1
    // Base case is the simplest possible case of our function
    if (n == 0) {
        return 1;
    }

    // Recursive case: n! = n * (n - 1)!
    // Recursive case defines how one problem relates to a similar, smaller problem.
    return n * factorial(n - 1);
}