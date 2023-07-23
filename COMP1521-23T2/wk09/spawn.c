// A program which runs the file_size program we wrote earlier!

#include <stdio.h>
#include <spawn.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void) {
    extern char **environ;
    pid_t pid;

    char *my_argv[] = {"./file_size", "file_size.c", NULL};

    int ret = posix_spawn(&pid, "./file_size", NULL, NULL, my_argv, environ);
    if (ret != 0) {
        perror("spawn");
        return 1;
    }

    ret = waitpid(pid, NULL, 0);
    if (ret == -1) {
        perror("waitpid");
        return 1;
    }

    return 0;
}