// For a given file path, print out what type of file it is using stat()

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        // Print an error message to stderr if used incorrectly
        fprintf(stderr, "Usage: %s <pathname>", argv[0]);
        return 1;
    }

    char *pathname = argv[1];

    // Get the stat for the file
    struct stat s;
    int ret = stat(pathname, &s);
    if (ret) {
        perror(pathname);
        return 1;
    }

    // st_mode not only contains permissions, it also tells us what sort of file we have!
    // These are, like permissions, represented as bit combinations, but we don't have to work with them as directly
    // There are predefined 'functions' for checking if a file is of a certain type
    // E.g. S_ISDIR(mode) checks if 'mode' represents a directory
    // There are also predefined bit masks for each type of file if you perfer working with the bits for some reason

    printf("The file '%s' is a ", pathname);

    // Check if this is a regular file
    if (S_ISREG(s.st_mode)) {
        printf("regular file\n");
    // Check if this is a directory
    } else if (S_ISDIR(s.st_mode)) {
        printf("directory\n");
    } else {
        // There are a few other file types, but they are beyond the scope of this course
        // See 'man 7 inode' for more :)
        printf("something else...\n");
    }

    return 0;
}