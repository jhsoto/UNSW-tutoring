// Read from "uppercase.txt" and write the same content but in lowercase to "lowercase.txt"

#include <stdio.h>
#include <ctype.h>

int main() {
    // fopen() takes the filename and open mode
    // In this case we have opened "uppercase.txt" for reading ("r")
    // This starts us from the beginning of the file without touching existing content
    FILE *uppercase = fopen("uppercase.txt", "r");
    // This "FILE *" type is what we call a file descriptor
    // It tracks where we are up to in the file (file pointer) like a cursor in a text editor
    // All file operations happen relative to this file pointer

    // fopen() can sometimes return NULL (e.g. if the file we are trying to read doesn't exist)
    // We need to check for these errors and handle them gracefully
    if (uppercase == NULL) {
        perror("uppercase.txt");
        return 1;
    }

    // Similarly, we open "lowercase.txt" for writing ("w")
    FILE *lowercase = fopen("lowercase.txt", "w");
    // Error checking on fopen()
    if (lowercase == NULL) {
        perror("lowercase.txt");
        return 1;
    }

    // fgetc() reads a BYTE (not specifically a character!) from the given file
    // It returns the byte read if successful
    // It returns EOF on a failed read (either we reached the end of the file or an error occurred)
    // Each time we read from the file, the file pointer is incremented so we don't keep reading the same byte
    int uppercase_byte;
    while ((uppercase_byte = fgetc(uppercase)) != EOF) {
        // Make the byte from an uppercase character to a lowercase character
        // Always check for existing helper functions for simple, common tasks like this!
        int lowercase_byte = tolower(uppercase_byte);

        // fputc() writes a BYTE (not specifically a character!) to the given file
        // It returns the byte written if successful
        // It returns EOF on a failed read (an error occurred)
        // Each time we write to the file, the file pointer is incremented so we don't keep writing in the same place
        fputc(lowercase_byte, lowercase);
    }

    // Always close a file after you are done with it!
    // Each program has a maximum number of open files
    // Closing a file also ensures all writes to it are done and aren't still buffered
    fclose(uppercase);
    fclose(lowercase);

    return 0;
}