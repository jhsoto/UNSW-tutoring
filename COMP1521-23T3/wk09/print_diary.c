// Print the content of the diary file stored at "$HOME/.diary"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    // My diary is stored in a file with path "$HOME/.diary"
    // "$HOME" is my home directory
    // For me, this is "/home/joshua" but this is probably different for you
    // So, for me, my diary has an absolute path of "/home/joshua/.diary"

    // "$HOME" is called an environment variable
    // These are variables from your terminal that can be accessed from within your programs!
    // Here we use the 'getenv' function to get the value of the "$HOME" environment variable
    char *home_dir = getenv("HOME");

    // Now we have to do some fun math to figure out how much space we need to store our full diary path
    // We need to a string with enough space to store:
    //  - the home directory path
    //  - './diary'
    //  - a null terminator
    size_t pathlen = sizeof(char) * (strlen(home_dir) + strlen("/.diary") + 1);
    // Now we can malloc space for our diary path...
    char *diary_path = malloc(pathlen);
    // ...and construct it using snprintf!
    // snprintf is printf that outputs to a string variable instead of the terminal
    snprintf(diary_path, pathlen, "%s/.diary", home_dir);

    // Now we can open our diary...
    FILE *diary = fopen(diary_path, "r");
    // ...and print all the bytes (characters) in it
    int diary_byte;
    while ((diary_byte = fgetc(diary)) != EOF) {
        putchar(diary_byte);
    }

    // Remember to close and free!
    fclose(diary);
    free(diary_path);

    return 0;
}