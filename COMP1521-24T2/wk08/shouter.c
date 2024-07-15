// Shout (make uppercase) everything written to stdin to stdout

#include <stdio.h>
#include <ctype.h>

int main(void) {
    // "stdin" and "stdout" are special files
    // They are pre-opened file descriptors we can use to access the terminal's input and output

    // Since these are just special files, we can use fgetc to read from stdin!
    int input;
    while ((input = fgetc(stdin)) != EOF) {
        // Convert our input to uppercase
        char output = toupper(input);

        // And we can use fputc to write to stdout!
        fputc(output, stdout);

        // Another common special file we use is "stderr"
        // This is where we usually write error messages to (like from perror)
        /* fputc(output, stderr);   - write our output to stderr */

        // stderr also goes to our terminal (by default) so printing to stderr doesn't *look* different
        // It does becomes different if you start redirecting input and output though... (see COMP2041)
    }

    return 0;
}