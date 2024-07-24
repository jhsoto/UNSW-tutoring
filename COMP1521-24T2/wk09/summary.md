# Week 9 Tutorial Summary
This week we continue looking at files with a focus on the **`stat`** function.  
We'll also take a quick looks at **environment variables** and **process creation.**

## Basic File Properties and `stat`
The operating system keeps track of a lot of information about each file in our file system.  
This includes things like:
- File size
- File type
- Last modification time
- Access rights (permissions)
- and more!

We can ask the operating system to give us this information using the **`stat` system call**.  
In C, this looks like calling the `stat` function described in `man 2 stat` (man 2 because it's a system call!)

### `stat(path, stat_struct)`
To call the stat function, we give it a *path* to the file we want to get information about and a *pointer to a `struct stat` variable.*  
The pointer we give stat is what the function will use to return the file's information to us.

`stat` will also return *`0` on success* and *`-1` on failure.*  
As with other operating system functions, **make sure to check this!!**  
`stat` uses `errno` just like other file operations so you can use `perror` and `strerror` to print nice error messages.

For example, to stat the file `hello.txt`:
```
struct stat s;
int err = stat("hello.txt", &s);
if (err != 0) {
    perror("stat");
    return 1;
}
```

The struct that `stat` returns is of the form (copied from `man 2 stat`):
```
struct stat {
    dev_t     st_dev;         /* ID of device containing file */
    ino_t     st_ino;         /* Inode number */
    mode_t    st_mode;        /* File type and mode */
    nlink_t   st_nlink;       /* Number of hard links */
    uid_t     st_uid;         /* User ID of owner */
    gid_t     st_gid;         /* Group ID of owner */
    dev_t     st_rdev;        /* Device ID (if special file) */
    off_t     st_size;        /* Total size, in bytes */
    blksize_t st_blksize;     /* Block size for filesystem I/O */
    blkcnt_t  st_blocks;      /* Number of 512B blocks allocated */

    time_t st_atime;  /* Time of last access */
    time_t st_mtime;  /* Time of last modification */
    time_t st_ctime;  /* Time of last status change */
}
```

Lots of these fields you won't have to touch for this course.  
Removing fields we don't use in COMP1521 leaves us with a struct looking like:
```
struct stat {
    mode_t    st_mode;        /* File type and mode */
    off_t     st_size;        /* Total size, in bytes */

    time_t st_atime;  /* Time of last access */
    time_t st_mtime;  /* Time of last modification */
    time_t st_ctime;  /* Time of last status change */

    /* For some challenge exercises */
    uid_t     st_uid;         /* User ID of owner */
    gid_t     st_gid;         /* Group ID of owner */
}
```
Let's break down a few of the simpler bits of information here...

### File Size
Super simple*, just the **number of bytes in the file.**

> *With some exceptions, including sparse files.  
> Technically this is the position of the last byte in the file, NOT the amount of bytes used on disk.  
> Take COMP3231/COMP3891 if the difference between those two interests you :)

### Access, Modify and Creation Time
Also pretty simple, the **time the file was last accessed (`st_atime`), modified (`st_mtime`) or was created (`st_ctime`).**  
Time is tracked by *couting the seconds since that 1st Janurary 1970* (the **Unix Epoch**).

This means comparing times is as simple as comparing integers.  
For example, if `st_atime > st_mtime` then the file was accessed more recently than it was modified.

### User and Group IDs (Advanced Topic)
On a UNIX system, each user is given an ID so it can track, for one thing, who owns what files.  
The ID of a file's creator is given by stat in the `st_uid` field.

UNIX systems also have what are called **groups**, which are *collections of users* that can be used to give multiple users special access/control over chosen files.  
Each group has an ID which can be attached to a file to give that group special permissions when accessing that file.

For example, some lecture slides might be created by the lecturer (UID 0) who has full access to the file.  
They can give course admins (GID 1) access to this file too so they can fix typos if they find any.  
Finally, a student (UID 1) who isn't part of the course admins group (GID 1) can be given access to the file such that they can only read but not modify the slides.

## The 'Mode' of a File
The `st_mode` field of the stat struct is one of the most useful, bits of information stat gives us.  
It contains two main pieces of information for us: the **type of the file** and the **access permissions.**

> Annoyingly, `st_mode` is not properly documented in `man 2 stat`.  
> Instead, full documentation for the mode is available in `man 7 inode`.

It stores both these values in one variable by using the *bits of the mode* to encode the required information.  
The format of `st_mode` at a high level looks like this:
```
st_mode = TTTT SSS PPPPPPPPP
          ^    ^   ^
          |    |   Permissions
          |    Special properties (ignored in 1521)
          File Type
```

Often the mode is expressed in **octal** largely due to permissions being separated into groups of 3 (as we will see shortly).

### File Types
The file type is encoded using **predefined patterns of 4 bits,** one for each different type of file.  
These are all documented in `man 7 inode`.

All these bit patterns have *bit masks* defined already by stat you can use in your programs.

#### Common Types
The most common file types you will come accross and their masks are summarised below:

| Mask #define | Bit Pattern | Corresponding File Type |
|--------------|-------------|-------------------------|
| `S_IFREG`    | `010 0000`  | Regular File            |
| `S_IFDIR`    | `004 0000`  | Directory               |

#### Less Common Types
Some other less common file types you *may* come across in this course or in the wild are:

| Mask #define | Bit Pattern | Corresponding File Type |
|--------------|-------------|-------------------------|
| `S_IFLNK`    | `012 0000`  | Symbolic Link           |
| `S_IFBLK`    | `006 0000`  | Block Device            |
| `S_IFCHR`    | `002 0000`  | Character Device        |
| `S_IFFIFO`   | `001 0000`  | FIFO (pipe)             |
| `S_IFSOCK`   | `014 0000`  | Socket                  |

Most of these are outside the scope of the course, so don't worry about them :)

#### Checking a File's Type
There are also convenient *macros* (essentially functions) that can check file types for you without you needing to manually do bitwise operations!

These are all given in `man 7 inode`, but the common ones you'll be using in this course are:
```
S_ISREG(mode) - check if the given mode is for a regular file
S_ISDIR(mode) - check if the given mode is for a directory
```

### Permissions
Permissions control **who has what type of access to a file.**  
There are 3 main permissions: **read, write and execute.**  
They are all fairly self-explanatory:
- Read: Whether a user can read the content of a file.
- Write: Whether a user can modify the content of a file.
- Execute: Whether a user can execute the file OR, for directories specifically, **open a directory.**

> NOTE: In UNIX, any file can be made executable, not just programs!  
> This means you can try (and most likely fail) to run as a program from your terminal any random text file or image file as long as it has execution permissions!

Permissions are also separated into *three groups*: **user, group and other** permissions.  
These correspond to:
- User: What permissions the **owner/creator** of a file has.
- Group: What permissions the group (if any) a file belongs to have.
- Other: What permissions every other user besides the owner and group have.

#### Permissions Bit Format
The permissions take up 9 bits of the mode.  
These 9 bits are divided into groups of 3 bits, where each group encodes read/write/execute permissions.  
A **`1` bit corresponds to allowing that type of access** and `0` corresponds to not allowing that type of access.  
Eeach of these groups of 3 bits then looks like this:
```
permissions = 0bR W X
                ^ ^ ^
                | | execute permission
                | write permission
                read permission

E.g. permissions = 0b110 -> read and write permissions only
```

Since permissions encode read, write and executes permissions for three categories of user (owner, group and other), the mode has **three sets of these RWX bits** like so:
```
permissions = 0b UUU GGG OOO
                 ^   ^   ^
                 |   |   Other permissions
                 |   Group permissions
                 User/Owner permissions

E.g. permissions = 0b 111 101 100
      user/owner -> read, write and execute permission
           group -> read and execute permission only
           other -> read permission only
```

As mentioned early, these permissions are why the mode is often represented in *octal.*  
For example, the permissions in the above example can be summarised in octal as `0b 111 101 100 = 0754`.

#### Testing Permissions
Testing permissions requires the use of bitwise operations, **making out permissions and checking that they are set.**  
This is made easier by using the *provided permissions masks* which I've copied from `man 7 inode` below:

| Mask #define | Mask Value | Corresponding File Type                         |
|--------------|------------|-------------------------------------------------|
| `S_IRWXU`    | `00700`    | owner has read, write, and execute permission   |
| `S_IRUSR`    | `00400`    | owner has read permission                       |
| `S_IWUSR`    | `00200`    | owner has write permission                      |
| `S_IXUSR`    | `00100`    | owner has execute permission                    |
|              |            |                                                 |
| `S_IRWXG`    | `00070`    | group has read, write, and execute permission   |
| `S_IRGRP`    | `00040`    | group has read permission                       |
| `S_IWGRP`    | `00020`    | group has write permission                      |
| `S_IXGRP`    | `00010`    | group has execute permission                    |
|              |            |                                                 |
| `S_IRWXO`    | `00007`    | others have read, write, and execute permission |
| `S_IROTH`    | `00004`    | others have read permission                     |
| `S_IWOTH`    | `00002`    | others have write permission                    |
| `S_IXOTH`    | `00001`    | others have execute permission                  |

Here's an example of how to use these masks to test for group write permission on `hello.txt`:
```
struct stat s;
int err = stat("hello.txt", &s);
if (err != 0) {
    perror("stat");
    return 1;
}

mode_t mode = s.st_mode;
if (mode & S_IWGRP) {
    printf("File has group write permission");
}
```

## Environment Variables
Environment variable are **a per process, global set of user defined variables** that all programs have access too.  
These are usually used to indicate configuration settings the user has setup including *timezones, language, home directory, and more!*

There are two main ways to access them in C:

### `getenv(env_var_name)`
`getenv` is a nice function that, given the name of an environment variable, will **return a string containing it's value** or *NULL if it cannot find that environment variable.*

Take a look at `print_diary.c` to see it in action :)

### `extern char **environ`
`environ` is a special variable you can 'include' in a function by using `extern` (don't worry too much about what extern does for this course).  
It is an **array of strings** that **contains all environment variables** which is a little harder to use than `getenv` but is useful when spawning new processes as we will see shortly.

It is very important **you declare `environ` exactly like shown below,** otherwise it won't work!
```
For example, to add `environ` to main:

int main() {
    extern char **environ;

    // ...
}
```

## Processes
Processes are the operating systems way of talking about all the **programs running on your computer.**  
We won't delve too much into the depths of how processes work in this course, but check out COMP3231/COMP3891 (Operating Systems) if you want to learn much, much more about them :)

Let's focus on how we can **spawn (create)** a new process using C code.

### `posix_spawn`
`posix_spawn` is a very scary, very powerful function that let's us create and start running new processes from within C.  
Rather than trying to explain in depth how it works, it's easier to just explain what the arguments are and give you some example code to copy :)

```
posix_spawn(pid, path, NULL, NULL, argv, env)
            ^    ^                 ^     ^
            |    |                 |     Environment variables (like 'environ')
            |    |                 Program arguments
            |    Path to program executable
            Pointer to return a process ID
```

And a full example of using `posix_spawn` is available in `spawn.c`.

Breaking down these arguments more:

#### PIDs
Like how files are given *file descriptors* by the OS, processes are given **process IDs** so the OS can track which process is which.  
You will need to use this, and the `waitpid(pid, NULL, 0)` function to wait for a process to finish executing after spawning it.

#### Path
The path to the executable file you want the spawned process to run.  
This could be something like `"ls"` or even `"./spawn"` to run the `spawn` program in your current directory.

#### Argv
You have to make your own argv array!  
This involves creating a list of strings that you want your spawned process to be given as its **argv array in main.**  

A fact about argv you might not have not known but need to know now is that **argv is NULL terminated!**
The *last item in argv is always NULL* instead of a string.

#### Env
An array of strings like argv representing environment variables for the spawned process to use.  
Usually you just steal `extern char **environ` and use the existing environment here.

That is all the depth I'll go into with `posix_spawn`.  
If/when you have to use it, I highly suggest copying code from this week's tute or the lectures rather than trying to do it from scratch.
