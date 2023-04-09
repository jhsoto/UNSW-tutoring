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

    // We create our stat struct that will be filled in by the stat() function
    // Note that we don't malloc it, we are only using it in this function so it can safely be on the stack
    struct stat s;
    // Calling stat() will fill in our stat struct and return 0 if it succeeds
    // We give it &s since stat() takes a 'struct stat *' (a pointer)
    int ret = stat(pathname, &s);
    if (ret) {
        // Something went wrong...
        perror(pathname);
        return 1;
    }

    // The size of the file is given in s.st_size (see 'man 3 stat' for more details)
    // st_size is of type off_t (long int)
    off_t size = s.st_size;
    printf("The file '%s' contains %ld bytes\n", pathname, size);

    return 0;
}