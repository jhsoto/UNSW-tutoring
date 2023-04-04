// Read from "uppercase.txt" and write the same content but in lowercase to "lowercase.txt"

#include <stdio.h>
#include <ctype.h>

int main() {
    // Open "uppercase.txt" for reading
    FILE *uppercase = fopen("uppercase.txt", "r");
    // Error checking on fopen()
    if (uppercase == NULL) {
        perror("uppercase.txt");
        return 1;
    }
    // Open "lowercase.txt" for writing
    FILE *lowercase = fopen("lowercase.txt", "w");
    // Error checking on fopen()
    if (lowercase == NULL) {
        perror("lowercase.txt");
        return 1;
    }

    // Read "uppercase.txt" one byte at a time
    int uppercase_byte;
    while ((uppercase_byte = fgetc(uppercase)) != EOF) {
        // Make the byte from an uppercase character to a lowercase character
        int lowercase_byte = tolower(uppercase_byte);
        // Write the lowercase character to "lowercase.txt"
        fputc(lowercase_byte, lowercase);
    }

    fclose(uppercase);
    fclose(lowercase);

    return 0;
}