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

    // Remember to free when you malloc!
    free(str);

    return 0;
}

char *makeString(char to_repeat, int n) {
    // We need to malloc as otherwise our string is placed on the stack.
    // The stack will be cleared when the function ends, deleting our string!
    char *new_str = malloc(sizeof(*new_str) * (n + 1));
    // new_str is a 'char *', so 'sizeof(*new_str)' is the same as 'sizeof(char)'
    // This trick (usually) works everytime you malloc!

    /* The for loop below is equivalent to:
    int i = 0;
    while (i < n) {
        ...
        i++;
    }
    */
    for (int i = 0; i < n; i++) {
        new_str[i] = to_repeat;
    }
    // Don't forget a null terminator!
    new_str[n] = '\0';

    return new_str;
}