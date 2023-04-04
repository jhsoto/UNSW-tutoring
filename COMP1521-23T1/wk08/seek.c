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

    // Seek to 3rd byte of file (position 2)
    // SEEK_SET seeks relative to the start of the file
    fseek(hello, 2, SEEK_SET);
    printf("3rd byte of file: '%c'\n", fgetc(hello));

    // Seek to the 6th byte after that (5 bytes further)
    // SEEK_CUR seeks relative to the current position in the file (the file pointer)
    // Remember that the previous fgetc() call already advanced the file pointer 1 byte further
    fseek(hello, 5, SEEK_CUR);
    printf("The 6th byte in the file after that is: '%c'\n", fgetc(hello));

    // Seek to 2nd last byte of file
    // SEEK_END seeks relative to the end of the file
    fseek(hello, -2, SEEK_END);
    printf("2nd last byte of file: '%c'\n", fgetc(hello));

    fclose(hello);

    return 0;
}