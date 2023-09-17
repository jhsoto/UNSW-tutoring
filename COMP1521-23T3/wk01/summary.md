# Week 1 Tutorial Summary

## Course Intro
What is this course about?
- Low level computing concepts
- Three main topics: **assembly, bitwise, operating systems (OS) concepts**

[Course website](https://elgar.cse.unsw.edu.au/~cs1521/23T3)
- [Course outline](https://elgar.cse.unsw.edu.au/~cs1521/23T3/outline/) - assessment details, course schedule, etc.
- [Course Forum](https://edstem.org/au/courses/13856/discussion/) - lab, lecture, assignment, etc. questions
- Week-by-Week - access to tutorial questions, lab exercises and weekly tests (week 3 onwards)
- [Submissions and marks](https://elgar.cse.unsw.edu.au/~cs1521/23T3/student/) - Check your assignment / lab autotests and marks (when they are released)

Summary of assessments (from course outline):
- Weekly Labs - 15%, usually due 12pm Monday the following week
- Assignments - both 15%, ass1: MIPS assembly, ass2: bitwise + OS
- Weekly tests - 10%, only includes best 6 of 8 tests (more details in week 3)
- Final exam - 45%, in person, hurdle of 40% (18/45)

## Memory
Memory hardware (items in bold are what the course covers at least a little)  
- **Registers**
- *Cache*
- **RAM** & *ROM*
- **Hard drives / SSDs**
- *CDs, DVDs, etc.*
- *Cloud*

### Memory Layout (RAM)
RAM (memory) is like a big array without a clear type  
It is just a collection of bytes (more on bytes later in the course...)  
There is a typical (simplified) layout of this memory so it stays organised

The below image is bit more complex than we need for this course but is nice for (almost) completeness :)
![image](https://media.geeksforgeeks.org/wp-content/uploads/memoryLayoutC.jpg)

The purpose of some key sections:  
**Text** - Code / Instructions  
**Data** - Global variables, string literals  
**Heap** - Malloc  
**Stack** - Local variables (and more in MIPS...)

### EXAMPLE - repeat.c
Think about where certain variables and other things are stored in memory...
Some examples:
- Printf strings like ```"Result %s\n"``` *(data)*
- Scanf strings like ```"%d"``` *(data)*
- The ```new_str``` var *(stack)*
- The actual string we create using malloc *(heap)*
- Function arguments *(stack)*


## Recursion
What is recursion?
-> Solving a problem using the solution to a smaller/easier version of the same problem

### Factorials (Recursively!)
The basic definition of a factorial is (roughly) 'the product an integer and all smaller integers greater than 0'  
For example:  
4! = 4 * 3 * 2 * 1  
5! = 5 * 4 * 3 * 2 * 1  

To make this **recursive**, we can observe that:
**5! = 5 * 4!**  
In general: n! = n * (n - 1)!

Some key terms with recursion...  
**Base case** - The most basic, fundamental solution to the set of problems  
-> for factorials either 1! or 0!  
**Recursive case** - The general case making use of recursion  
-> for factrorials this is 'n! = n * (n - 1)!'

### EXAMPLE: factorial.c
A quick refresher on argc and argv...  
**argc** - number of command line arguments  
**argv** - an array of command line arguments (strings)  

Also, check out 'man pages'  
They provide details about every C function you can think of! (probably)  
You can use ```man 3 <C function>``` in the terminal to acces them  
E.g. ```man 3 atoi```

>NOTE: The '3' is there because the man pages are so large that they are divided into sections. Section 3 covers most normal C functions. Without the '3' it tries to guess which section you want which can sometimes lead you to the wrong place...
