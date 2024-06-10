// Replace all negative numbers in an array with zero
#include <stdio.h>

#define ARRAY_SIZE 10

int main() {
    int numbers[ARRAY_SIZE] = {1, -2, 3, 4, -5, 6, 7, -8, -9, 10};

    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (numbers[i] < 0) {
            numbers[i] = 0;
        }
    }

    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    return 0;
}