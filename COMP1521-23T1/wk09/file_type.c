// For a given file path, print out what type of file it is using stat()

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        // Print an error message to stderr if used incorrectly
        fprintf(stderr, "Usage: %s [pathname]", argv[0]);
        return 1;
    }

    char *pathname = argv[1];

    printf("The file '%s' is a ", pathname);


    // TODO: Print out file type of the file with the given pathname


    return 0;
}