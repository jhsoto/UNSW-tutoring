// Read text from stdin and output it to "output.txt"

#include <stdio.h>

int main() {
    // Open "output.txt" for writing
    // Opening a file for writing creates the file if it doesn't exist and removes all existing content
    FILE *output = fopen("output.txt", "w");
    // Error checking on fopen()
    if (output == NULL) {
        perror("output.txt");
        return 1;
    }

    int byte_to_write;
    // getchar() is just a special case of fgetc() that always reads from stdin
    // getchar() <=> fgetc(stdin)
    while ((byte_to_write = fgetc(stdin)) != EOF) {
        // fputc() writes a BYTE (not specifically a character!) to the given file
        // It returns the byte written if successful
        // It returns EOF on a failed read (an error occurred)
        // Each time we write to the file, the file pointer is incremented so we don't keep writing in the same place
        fputc(byte_to_write, output);
    }

    fclose(output);

    return 0;
}