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


    // TODO: Copy "uppercase.txt" content to "lowercase.txt" in lowercase


    fclose(uppercase);
    fclose(lowercase);

    return 0;
}