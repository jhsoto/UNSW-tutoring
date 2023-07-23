// Tests if files given to the program are executable

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        // Print an error message to stderr if used incorrectly
        fprintf(stderr, "Usage: %s [pathnames]", argv[0]);
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

    // st_mode mainly contains the permissions for a given file
    // The permissions of a file are what determine if someone is able to read/write/execute a file
    // There are 3 categories users which you can have different permissions:
    //     - Owner: the user who created the file
    //     - Group: a collection of users (e.g. COMP1521 students)
    //     - Other: all remaining users not covered by one of the other categories
    // These permissions are encoded in the bits of the st_mode field:
    //     0b 001000 000 111 110 010
    //        ^      ^   ^   ^   ^
    //        |      |   |   |   other permissions (write only)
    //        |      |   |   group permissions (read & write only)
    //        |      |   owner permissions (read, write and execute)
    //        |      other options beyond the scope of this course (see man 7 inode)
    //        what type of file we have
    // Permissions (and the mode) are usually written in OCTAL (3 binary digits or bits -> 1 octal digit)
    //     0  10     0   7   6   2       -> 0100762 is the mode from above written in octal

    // Here we use pre-defined bit masks to check if any of the user categories have execution permissions
    // E.g. st_mode & S_IXUSR:
    // st_mode: 0b 001000 000 111 110 010
    // S_IXUSR: 0b 000000 000 001 000 000 &     <- masks out just the bit representing the owner's execution permission
    //        = 0b 000000 000 001 000 000
    // This is non-zero, so C would treat this as 'True'
    if (s.st_mode & S_IXUSR || s.st_mode & S_IXGRP || s.st_mode & S_IXOTH) {
        printf("%s is executable!\n", pathname);
    } else {
        printf("%s is not executable :(\n", pathname);
    }
}