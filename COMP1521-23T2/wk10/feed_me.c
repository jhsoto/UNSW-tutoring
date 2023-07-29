// Prints a message - "feed me input!\n" - while also reading user input at the same time.
// Repeat any lines input by the user back to stdout.

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>     // For sleep()

#define MAX_LINE 1024

// All functions run by a thread must have a similar function signature to this.
// I.e. must return a 'void *' and must take one 'void *' argument.
// The name of the function and the argument can be changed.
void *thread_run(void *data) {
    // This thread is going to be stuck in an infinite loop
    while (1) {
        printf("feed me input!\n");
        sleep(1);
    }

    // Will never reach this
    return NULL;
}

int main() {
    char line[MAX_LINE];

    // A thread handle - identifies a particular thread
    pthread_t thread;
    pthread_create(
        &thread,        // The thread handle for the newly created thread is returned here
        NULL,           // Thread attributes - not important for this course, left as NULL
        thread_run,     // The function for the new thread to run
        NULL            // Argument for the thread function - a pointer
    );

    // Read lines from stdin until EOF is read
    while (fgets(line, MAX_LINE, stdin) != NULL) {
        printf("you entered: %s", line);
    }

    // Usually we would wait for the thread to finish before exiting, but our thread is
    // in an infinite loop, so would never finish.
    // We could use 'pthread_cancel(thread)' to stop it, but exiting the program will force
    // all created threads to stop anyway.

    return 0;
}