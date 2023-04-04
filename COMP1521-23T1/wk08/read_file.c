// Read content from "hello.txt" and output it to stdout

#include <stdio.h>

int main() {
    // fopen() takes the filename and open mode
    // In this case we have opened for reading ("r")
    // This starts us from the beginning of the file without touching existing content
    FILE *hello = fopen("hello.txt", "r");
    // This "FILE *" type is what we call a file descriptor
    // It tracks where we are up to in the file (file pointer) like a cursor in a text editor
    // All file operations happen relative to this file pointer

    // fopen() can sometimes return NULL (e.g. if the file we are trying to read doesn't exist)
    // We need to check for these errors and handle them gracefully
    if (hello == NULL) {
        // perror() is a special function that prints an appropriate error message
        // It can tell what error just occurred by using the global variable 'errno'
        // fopen() (like many other functions) indicates which error occurred by changing 'errno'
        perror("hello.txt");
        return 1;
    }

    // fgetc() reads a BYTE (not specifically a character!) from the given file
    // It returns the byte read if successful
    // It returns EOF on a failed read (either we reached the end of the file or an error occurred)
    // Each time we read from the file, the file pointer is incremented so we don't keep reading the same byte
    int byte_read;
    while ((byte_read = fgetc(hello)) != EOF) {
        putchar(byte_read);
        // putchar() is just a special of fputc() that writes to stdout
        // putchar(byte_read) <=> fputc(byte_read, stdout);
    }

    // We could also use fgets() which reads the next null terminated string from the file
    // We can't use this on files that we expect to have '\0' bytes as part of normal data
    // Takes in the size of the buffer (array) given to prevent overflow
    // This code is commented out to prevent reading past the end of the file!
    /*
    char bytes_read[50];
    if (fgets(bytes_read, 50, hello) == NULL) {
        perror("fgets");
        return 1;
    }
    printf("%s", bytes_read);
    */

    // Always close a file after you are done with it!
    // Each program has a maximum number of open files
    // Closing a file also ensures all writes to it are done and aren't still buffered
    fclose(hello);

    return 0;
}