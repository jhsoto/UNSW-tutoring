// Creates a string containing a repeated character
#include <stdio.h>
#include <stdlib.h>

char *makeString(char to_repeat, int n);

int main() {
    char to_repeat;
    int n;

    printf("Character to repeat: ");
    scanf("%c", &to_repeat);

    printf("Times to repeat: ");
    scanf("%d", &n);

    char *str = makeString(to_repeat, n);
    printf("Result: %s\n", str);

    return 0;
}

char *makeString(char to_repeat, int n) {
    // TODO
}