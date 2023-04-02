// Print bytes from various locations in "hello.txt"

#include <stdio.h>

int main() {
    // Open "hello.txt" for reading
    FILE *hello = fopen("hello.txt", "r");
    // Error checking on fopen()
    if (hello == NULL) {
        perror("hello.txt");
        return 1;
    }

    // TODO: Seek to 3rd byte of file (position 2)
    printf("3rd byte of file: '%c'\n", fgetc(hello));

    // TODO: Seek to the 4th byte after that (3 bytes further)
    printf("The 4th byte in the file after that is: '%c'\n", fgetc(hello));

    // TODO: Seek to 2nd last byte of file
    printf("2nd last byte of file: '%c'\n", fgetc(hello));

    fclose(hello);

    return 0;
}