// Prints a message - "feed me input!\n" - while also reading user input at the same time.
// Repeat any lines input by the user back to stdout.

#include <stdio.h>
#include <pthread.h>

#define MAX_LINE 1024

void *thread_run(void *data) {

    // TODO: Print "feed me input!\n" every second

}

int main() {
    char line[MAX_LINE];

    // TODO: Spawn a thread to call thread_run()

    // TODO: Repeat user input from stdin back to stdout

}