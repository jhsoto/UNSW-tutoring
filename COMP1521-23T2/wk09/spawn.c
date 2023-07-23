// A program which runs the file_size program we wrote earlier!

#include <stdio.h>
#include <spawn.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void) {
    // We can get an array of every environement variable (as a string) like so:
    extern char **environ;

    // 'posix_spawn' lets us (forces us to) create our own argv array
    // Some things to remember about 'argv' that are important:
    //  - First argument is the name of the program
    //  - Options are arguements (e.g. 'ls -l' has argv = ['ls', '-l'])
    //  - Final argument is a 'NULL' terminator
    char *my_argv[] = {"./file_size", "file_size.c", NULL};

    // A 'pid' is an id (identifier) that the operating system uses to track processes
    // Processes are any program that your computer is running (e.g. google chrome, spotify, vscode, etc.)
    pid_t pid;
    // 'posix_spawn' is a function that allows us to run other programs (processes) from our program
    // Here's a quick breakdown of how to call it (ignoring some of the more advanced arguments where we just use 'NULL')
    int ret = posix_spawn(&pid, "./file_size", NULL, NULL, my_argv, environ);
    //  ^                 ^     ^                          ^        ^
    //  |                 |     |                          |        Array of environment variables
    //  |                 |     |                          Array of arguments
    //  |                 |     Program to run
    //  |                 Where to place the process id given to the created process
    //  Return value (0 on success)

    // Error checking as always for operating system functions
    if (ret != 0) {
        perror("spawn");
        return 1;
    }

    // 'waitpid' is a function that pauses this program until the program with the given 'pid' finishes
    // In this case, waits for the program we just spawned to finish
    ret = waitpid(pid, NULL, 0);
    // Error checking!!
    if (ret == -1) {
        perror("waitpid");
        return 1;
    }

    return 0;
}