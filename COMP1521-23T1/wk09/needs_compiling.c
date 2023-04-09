// Check if a given program needs to be recompiled
// A program needs to be recompiled if the C source was modified more recently than the executable program

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        // Print an error message to stderr if used incorrectly
        fprintf(stderr, "Usage: %s [executable path]", argv[0]);
        return 1;
    }

    // We are given the pathname of the executable
    char *executable_pathname = argv[1];

    // Source path is: executable path + .c + null terminator
    int source_pathname_len = strlen(executable_pathname) + 2 + 1;
    // Malloc space for the source pathname
    char *source_pathname = malloc(source_pathname_len * sizeof(char));

    // Append ".c" to the name of the executable to (hopefully) get the name of the C source file
    // Copy the executable pathname
    strncpy(source_pathname, executable_pathname, source_pathname_len);
    // Append ".c"
    strcat(source_pathname, ".c");

    // Get stat for the executable
    struct stat executable_stat;
    int ret = stat(executable_pathname, &executable_stat);
    if (ret) {
        perror(executable_pathname);
        return 1;
    }

    // Get stat for the source file
    struct stat source_stat;
    ret = stat(source_pathname, &source_stat);
    if (ret) {
        perror(source_pathname);
        return 1;
    }

    // If the source's last modified time is after the executable's last modified time we need to recompile
    // Modification time is stored in the st_mtime field of the stat struct (see 'man 3 stat' for more details)
    if (source_stat.st_mtime > executable_stat.st_mtime) {
        printf("'%s' needs to be recompiled!\n", executable_pathname);
    } else {
        printf("'%s' does not need to be recompiled.\n", executable_pathname);
    }

    return 0;
}