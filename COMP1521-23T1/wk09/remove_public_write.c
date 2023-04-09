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
    // Get the stat for the file
    struct stat s;
    int ret = stat(pathname, &s);
    if (ret) {
        perror(pathname);
        // Move on to the next file
        return;
    }

    // The permissions (and file type) of a file is stored in s.st_mode (see 'man 3 stat' AND 'man 7 inode' for more details)
    mode_t mode = s.st_mode;

    // The permissions are stored as the least significant 9 bits of st_mode
    // They are grouped into user (owner) permissions, group permissions and other (public) permissions
    // E.g. 101 100 110
    //      ^   ^   ^ Other (public)
    //      ^   ^ Group
    //      ^ User (owner)
    // Each set of three bits represents read (r), write (w) and execute (x) permissions in that order
    // E.g. 101 100 110
    //      r-x r-- rw-

    // S_IWOTH is a #define included with stat.h that masks out the public write permission bit
    // There are lots of provided masks, check out 'man 7 inode'
    // This condition extracts the public write permission bit and makes sure it isn't set
    // E.g. mode: 101 100 110
    //   S_IWOTH: 000 000 010 &
    //         -> 000 000 010 (non-zero = true)
    if (!(mode & S_IWOTH)) {
        printf("'%s' is already not publicly writable\n", pathname);
        return;
    }

    // If we are here, we are removing an existing public write permission
    printf("Removing public write permission from %s\n", pathname);

    // Now we want to clear the bit representing the public write permission
    // 'mode & ~mask' will clear all the bits in 'mode' corresponding to places with a '1' bit in 'mask'
    // Essentially, we extract all BUT the masked bits from 'mode' (like a reverse extract)
    // E.g. mode: 101 100 110
    //  ~S_IWOTH: 111 111 101 &
    //         -> 101 100 100 (cleared public write permission bit)
    mode_t new_mode = mode & ~S_IWOTH;

    // Now we use chmod() to modify the permissions (technically the whole mode) of the original file
    // chmod() takes the pathname of the file to modify permissions of and the new mode
    // The return value is just used for error checking as usual
    ret = chmod(pathname, new_mode);
    if (ret) {
        perror(pathname);
        // Move on to the next file
        return;
    }

    // Done!
}