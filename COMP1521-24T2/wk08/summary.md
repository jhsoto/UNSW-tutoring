# Week 8 Tutorial Summary
This week marks the start of the last topic for 1521 - an intro to **operating system** level concepts.  
In particular, we will be looking at **files** this week.

## High Level View of Files
Most of you should be used to working with files on a computer in some capacity, so I'll try to keep this section short.

An important note to make right away though, is that we'll be looking at a **UNIX-like** file system.  
There are lots of different ways to handle files, and different operating systems do so differently so don't expect everything we talk about in this part of the course to translate exactly onto (for example) a windows machine!

### Regular Files
Regular files are what you expect a file to be: a **collection of data with an associated name.**  
That is all a file is to the operating system, a bunch of data, more specifically *bytes.*  
There are no types or enforced formats, just clumps of data.

This means **anything that is just data is a regular file** regardless of what kind of data the file is storing.  
Some types of data a regular file might store include:
- Text
- Images
- Video
- Programs
- Video games
- Compressed data (like a .zip file)
- And so much more!

### Directories
A.k.a. **folders**, directories store a collection of files.  
Directories can store *any type of file* including *other directories.*

#### Directory Heirarchy
UNIX uses directories as the basis for *organising its file system.*  
A typical **directory heirarchy** - a tree-like structure showing directories and their contents - looks like this:  
![A typical UNIX directory heirarchy](https://cgi.cse.unsw.edu.au/~cs1521/24T2/tut/08/q-fs-objects/filesystem.png)

Here we can see a **root** directory '`/`' which contains 4 other directories: '`bin`', '`dev`', '`home`' and '`usr`'.  
These are all directories you will almost certainly find on any UNIX machine which all have an important purpose:

- '`/bin`' contains *binary executables* (**programs**) that, mostly, come with the system
- '`/dev`' contains *device files* (I'll come back to those)
- '`/home`' contains *user specific files* - this is where most of the files you are used to working on live!
- '`/usr`' contains *user installed programs* - extra programs not installed by default

There are more standard directories than this but you can look those up yourself...

The key takeaway here is that we have a *root* directory containing all other directories creating a tree-like structure connecting all our files together.

### Paths
Paths are how we **refer to specific files** in our filesystem.  
A path is made up of *the directory chain leading up to the directory containing the target file* and the *file's name.*  
Each directory in the chain is **separated by a '`/`' character** with an optional '`/`' after the final file name.

For exmaple, using the above directory heirarchy, the path for the *work* file in the *jas* directory would be '`/home/jas/work`'.

### Special Directories / Paths
Writing paths out like we did above is probably not what you're used to doing when opening files say when doing a lab exercise.  
Normally, you can just type something like '`code exercise.c`' and it just opens the file!

The path '`/home/jas/work`' is called an **absolute path.**  
An absolute path **always starts from the root directory.**

But absolute paths, as you might be able to guess, get very very long, so there are a few special directories / paths you can use as shortcuts...

#### Working Directory
This is the one you probably use the most and don't even realise!  
When you run a program, including programs like *the terminal*, it runs **within a directory.**  
This directory is called the **working directory** and any (non-absolute, not starting with '`/`') paths you use within that program are treated as **relative to the working directory.**

For example, if we ran our terminal in the '`/home/jas`' directory, we could open '`work`' in vscode by just typing '`code work`' into the terminal.  
The terminal automatically will know to look for '`work`' in the '`/home/jas`' directory, effectively opening '`/home/jas/work`' just like we did with an absolute path.

#### Current and Parent Directory
These are nice shortcuts for accessing relative to the working directory.

'`.`' is a special directory that exists in each directory and **refers to itself.**  
For example, '`/home/jas/work`' is the same file as '`/home/jas/./work`' and even '`/./home/././jas/./././././work`'.

'`..`' is similar to '`.`' but **refers to the parent directory.**  
For example, '`/home/jas/..`' refers to '`/home`' and '`/home/jas/../jas/work`' is the same file as '`/home/jas/work`'.

#### Home Directory
The home directory is a user-defined directory that you can get a quick shortcut to by including '`~`' at the start of a path.  
Often, the home directory is set to **the directory containing most of a user's files.**

For example, a sensible home directory in the above file system would be '`/home/jas`'.  
You could then access the '`work`' file using the path '`~/work`'.

### Other File Types
Some other less common (largely out of scope for 1521) file types include:

- Symbolic links - shortcuts to other files (opening a symbolic link will open the file it is linked to instead)
- Hard links - coupled files who share underlying data (modifying ones modifies the other)
- Pipe - sends data written to this file to another location
- Socket - a network connection

#### Devices
A major subcategory of files is **device files.**  
UNIX handles devices in a really clever way - *all devices are treated like files.*  
This means send data to a device looks like writing to a file, and receiving data from a device looks like reading from a file.  
Most device files **live in the '`/dev`' directory.**

For example, there could a file for a printer which prints data written to that file and gives the printer's ink levels by reading from the same file.

## Key File Terms and Concepts
Before digging into the functions we'll be using to work with files, let's introduce some key terms and concepts.

### Syscalls
Not really a new concept, but it is important to understand that **files are handled by the operating system,** and as we saw in MIPS, this means all file operations work using **syscalls.**  
We won't have to use the raw syscalls themselves, but it is important to understand that ***most of the file functions we use are just wrappers around a syscall.***

### File Descriptors
File descriptors are **identifiers** the operating system uses and gives and our program so it knows **what file to operate on** when performing a file operation like reading or writing.

We don't generally use the file descriptors given by the OS directly in this course.  
The functions we use will give/take '`FILE *`' type objects which are basically a file descriptor with some extra stuff we don't have to worry about :)

#### Special File Descriptors
There are a few special file descriptors which are **open by default** when you start a program.  
These are:
- `stdin`: Standard input
- `stdout`: Standard output
- `stderr`: Standard error

These files, usually connected to your terminal, are where you program will, unless told otherwise, look for **input (`stdin`)**, print **output (`stdout`)** and print **error messages (`stderr`).**

Functions like `printf()` and `scanf()` use these file descriptors when reading/writing data.

### File Pointers / Cursors
When you do file operations, the operating system also tracks **your position in the file** by using what's called a **file pointer** or **file cursor.**  
These are an OS-internal tracker, much like the vertical bar you see in text-editors that indicate where in the file you are editing.

All read + write operations are performed **relative to the file pointer.**  
Most operations *automatically move the file pointer* so when you read/write data you don't have to manually advance through the file.

### EOF
EOF, like a null terminator for strings, is an indicator that **a byte was read from the end of a file.**  
Unlike null terminators, **it is not an actual value stored in the file!**
It is just a special return value from file functions indicating the end of the file was reached.

## File Operations
Now, let's finally get to the main file operations we'll be using in our C code:

### Open - '`fopen(path, mode)`'
Before you can do any actual reading/writing to a file, you have to **open** it!  
All you need to do is give '`fopen`' the **path** to the file you want to open and the **mode** you want to open the file using.  
It will return a '`FILE *`' which you can then pass to the rest of the file functions to operate on that file.

#### Open Modes
There are a lot of what are called 'modes' to choose from when opening a file.  
They provide useful options and allow/disallow reading/writing.  
The main modes we will use are:
- '`r`': **Read** mode, the file pointer starts at the *beginning of the file*
- '`w`': **Write** mode, the file pointer starts at the *beginning of the file* AND *any data that was in the file before is deleted*
- '`a`': **Append** mode, open for writing, but *doesn't clear the old file data* AND the file pointers starts at the *end of the file*

For a full list of the open modes, check out '`man 3 fopen`'.

### Close - '`fclose(file)`'
Closes a file, indicating you are done with it.  
Usually it doesn't cause problems if you forget to close a file, but there are some more advanced edge cases where it does matter including:
- Running out of file descriptors
- Buffered writes not being written back to the file until it is closed

These are not issues we worry too much about, but **make sure you close all files you open** anyway!

### Read - '`fgetc(file)`'
Returns the **next byte from the file** where 'next' means *the byte in the position given by the file pointer*.  
If there is no next byte because it is the end of the file, this returns `EOF`.

### Write - '`fputc(byte, file)`'
Write the given byte to the **next position in file** where 'next' means *the byte in the position given by the file pointer*.

#### Read, Write and Bad Function Names
A very important point to make here is that, despite their names, **`fgetc` and `fputc` do not only read characters!**  
They read characters in the `char` type sense, not the ASCII sense.  
Effectively, these functions **return bytes from the file** even if those bytes aren't valid ASCII characters.

### Seek - '`fseek(file, offset, whence)`'
Seek is a function that lets you **directly modify the file pointer.**  
You give it an offset to set the file pointer to and a 'whence' which determines *what the offset is relative to.*  
'Whence' can do one of three options:
- `SEEK_SET`: the start of the file
- `SEEK_CUR`: the current file pointer position
- `SEEK_END`: the end of the file

### Error Handling - '`perror(message)`'
Most operating system functions, including file functions can fail for numerous reasons.  
To help with error handling, a 'secret', global variable called `errno` exists which is used by operating system functions **to indicate what error occurred** when they fail.  
A handy function called **`perror()`** can take the value of `errno` and **print a relevant error message** along with whatever additional message you give it as an argument.

It is super important to **always error check file operations** and any OS operation in general.  
To see how a function reports errors, check out the man page for that function!  
Some common return values OS functions use to indicate errors include:
- `NULL`
- `EOF`
- A negative value

### Other Reading/Writing Functions
There are a lot of different reading/writing functions to choose from.  
For this course, there is no need to go beyond `fgetc` and `fputc` but you are welcome to use any (sensible!) function you want.

Some other common reading/functions are:
- `getchar()` & `putchar()`: Same as `fgetc(stdin)` and `fputc(stdout)` respectively
- `fgets()` & `fputs()`: Read/write entire strings
- `printf()` & `scanf()`: Formatting printing/reading to `stdout` and `stdin` respectively, a classic :)
- `fprintf()` & `fscanf()`: Formatting printing/reading to/from a specific file
- `snprintf()` & `sscanf()`: Formatting printing/reading to/from a string buffer
- `fread()` & `fwrite()`: Read/write using a given buffer to store data in / write data from respectively

> Be very careful when using the `scanf` family of functions for input from files!  
> Usually you are better off using a simpler input function because `scanf` tends to do weird things and is generally overkill for the tasks asked of you in this course.

> NOTE: You may come across a function called `gets()` at some point, **DO NOT USE THIS FUNCTION!!!**  
> **Use `fgets()` instead.**  
> `gets()` does not check for buffer overflows, meaning if the user types a really long string, it will just crash your program!
> `fgets()` takes the length of the buffer it's reading into as an argument so it can check for buffer overflows and stop reading as needed.


## Man pages
A final note on a very, very useful resource you have available to you whenever you have a terminal (including in the exam!)  
**The man pages** are a set of manual entries for various C functions, terminal commands, system calls, and more!  
They are divided into sections and can be accessed using the '`man <section> <function>`' command in the terminal.

For example, to look for the '`fopen`' C function, you would type '`man 3 fopen`'.

> **BE WARNED -- Man pages are intimidating!**  
> They contain more information than you probably need and are very detailed.
> The main sections to look out for in man pages are:  
> **SYNOPSIS** for *function signatures* (how to call the function and what it returns)  
> **DESCRIPTION** for a (sometimes) quick *summary of what the function does*  
> **RETURN VALUE** for details on how the return value is used, most notably for *indicating success/failure conditions*  
> Try to get some practice using them as they will be incredibly useful in the exam if you can get used to them.