// Create and print a struct of favourite things
#include <stdio.h>

// A struct to hold a favourite letter and number
struct favourite {
    int number;
    char letter;
};

int main(void) {
    // Create a favourite struct
    struct favourite faves;
    faves.number = 7;
    faves.letter = 'Q';

    // Print it out
    printf("My favourite number is: %d\n", faves.number);
    printf("My favourite letter is: %c\n", faves.letter);

    return 0;
}