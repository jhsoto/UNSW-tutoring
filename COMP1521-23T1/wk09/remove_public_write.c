// Remove public write permission from files given as command line arguments if they have it

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void remove_public_write(char *pathname);

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        remove_public_write(argv[i]);
    }
    return 0;
}

void remove_public_write(char *pathname) {

    // TODO: check if the given file has public write permissions

    // TODO: remove public write permissions if it does

}