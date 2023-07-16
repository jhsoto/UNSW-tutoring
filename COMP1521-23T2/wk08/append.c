// Append a message to "append.txt"

#include <stdio.h>

int main() {
    char message[] = "Hello there!\n";

    // Open "append.txt" for appending
    // The append mode lets us write to the file without removing existing content
    // The file pointer starts the end of the file
    FILE *append = fopen("append.txt", "a");

    // fputs() lets us write strings to a file
    // We don't error check as a failed write does not affect the rest of this program
    fputs(message, append);

    fclose(append);

    return 0;
}