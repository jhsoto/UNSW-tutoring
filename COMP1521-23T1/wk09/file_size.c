// For a given file path, print out how large it is (in bytes) using stat()

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


    // TODO: Figure out the size of the file with the given pathname


    printf("The file '%s' contains %ld bytes\n", pathname, 42);

    return 0;
}