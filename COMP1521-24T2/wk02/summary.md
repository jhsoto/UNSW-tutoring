# Week 2 Tutorial Summary

## MIPS Intro
MIPS is an *assembly* language.  
Each line of MIPS code is an **instruction** which maps (almost) exactly onto actual operations your CPU itself can perform.

This means most of C's 'high-level' features are not present in MIPS!  
Most notably, **MIPS does not have...**
* Control structures (like `if(...)` statments and loops)
* Arrays
* Functions
* Structs

All of these are abstractions implemented by C that *don't exist in assembly languages!*  
This means **we will need to come up with ways to implement these features ourself...**

### Overview of MIPS
Your main source of information for MIPS is the
[MIPS Documentation](https://cgi.cse.unsw.edu.au/~cs1521/24T2/resources/mips-guide.html)
page on the course website.  
You also have access to this page in the final exam :D

The main things to know for now with MIPS are...

#### [Registers](https://cgi.cse.unsw.edu.au/~cs1521/24T2/resources/mips-guide.html#registers)
Tiny **32-bit memory devices** within your CPU  
The closest thing to variables in C  
Organised into a few groups/types of registers  
Important types of registers for this week (more types and uses to come later)  
  - **$t0 - $t9**: *temporary* registers
    - Our go-to, general purpose registers 
    - Usually used for local variables
  - **$a0 - $a3**: *argument* registers
    - For this week, only used for *syscalls*
  - **$v0 - $v1**: *return value* registers
    - For now, also only used for *syscalls*
  - **$ra**: *return address* register
    - You shouldn't need to use this yourself yet, but you will notice it being used at the end of your code in '`jr $ra`'
    - For now, just recognise that '`jr $ra`' is how your program returns from the main function :)


#### [Instructions](https://cgi.cse.unsw.edu.au/~cs1521/24T@/resources/mips-guide.html#instructions)
The individual operations that make up your MIPS programs  
Correspond with **actual operations your CPU hardware can perform**  

> **Sidenote:** MIPS instructions the correspond directly with CPU operations are called *native instructions*. Not all instructions are native. Some are *pseudo-instructions* which are actually exectuted using multiple native instructions.

There are a lot of instructions, so **try not to overwhelm yourself by reading through or trying to memorise all of them!!**
You'll see the most useful instructions in tutes/lectures/labs already so stick to those as often as possible :)

#### [Syscalls](https://cgi.cse.unsw.edu.au/~cs1521/24T2/resources/mips-guide.html#syscalls)
Syscalls are probably one of the most different and new thing you'll see in MIPS code.  
Syscalls are like **function calls to the operating system (OS).**  
Some operations like *reading user input* or *printing output* are handled by the OS.  
You need to tell the OS when you want it to perform one of these operations.  
The basic structure of performing a syscall is as follows:  

1. Load the *syscall number* into the **$v0** register  
This register is where the OS will look to determine which system call to perform.  
As code: `li      $v0, 1`

2. Load any *arguments* into the **$a0** register  
For some syscalls the OS will need more data from you to complete the syscall.  
For example, to print an integer, the OS needs to know *what integer to print*.  
As code: `li      $a0, 42`

3. **Do the syscall!**  
Syscalls are invoked (called) using the `syscall` instruction.  
Executing this instruction lets the OS take over and complete the syscall you asked for.  
As code: `syscall`

4. Handle *return values* placed in the **$v0** register  
Some syscalls (like *reading an integer*) have return values.  
The OS places the return value in the **$v0** register during the `syscall` instruction.  
As code: `move    $t0, $v0`

#### An example syscall
```
# Syscall to print the integer '42'
li      $v0, 1
li      $a0, 42
syscall
```
> NOTE: The order you setup the $a0 and $v0 registers **does not matter.**
As long as both registers have the value you want in them by the time you perform the syscall (the `syscall` instruction), you're all good :)


### Example: square.s
A basic MIPS example to get used to instructions and syscalls.  
Nothing much more to note :)


## MIPS Control Structures
The most important control structures from C we want to implement in MIPS are **if statements** and **while/for loops**.

The main tools we have for both of these are **branch instructions** and **labels**.

### Labels and branching
These are our tools for controlling *the order our MIPS code is executed in*.

[**Branch instructions**](https://cgi.cse.unsw.edu.au/~cs1521/24T2/resources/mips-guide.html#insn-brjmp)
let us change which instruction will be executed next.  
Normally MIPS just executes instructions from top to bottom, but branches let us jump around our code.  
Often, the branch will be *conditional*, meaning we will only jump to a different instruction **if some condition is true** (a lot like an `if(...)` statement!)  

**Labels** are how we can control where we jump to using branch instructions.  
They are like *markers* that we can give to branch instructions so they know which part of the code we want to execute next.


### `if(...)` Statements in MIPS
Since we have **conditional branch instructions**, a lot of the work for if statements is already done for us!  

The main things we have to worry about are:  
* What branch instruction to use
* Where to put our labels so we branch/jump to the correct code

In general, a MIPS if statement will looks something like:
```
if_cond:
        <some branching condition> if_else
if_body:
        <body of the if>
        b   if_end
if_else:
        <body of the else>
if_end:
        <code immediately after the if statement>
```
Often we want to **invert the condition from the C code** so that the branch will *skip the body when the original condition was false* just like a normal if statement would.

#### A quick example
In C:
```
if (num > 0) {
    // Do stuff
} else {
    // Do other stuff
}
// Done
```
In MIPS:
```
    # $t0: num
if_cond:
    # Branch when $t0 <= 0
    ble     $t0, 0, if_else     # if (num > 0)
if_body:
    # Do stuff
    b       if_end
if_else:
    # Do other stuff
if_end:
    # Done
```

### Example: adult.s
A basic if statement in MIPS.  
Nothing much to note, very similar to the example above.

### Example: teen.s
A more complex if statement in MIPS.  
Conditions like `<cond1> && <cond2>` or `<cond1> || <cond2>` are best translated using **two branch instructions.**
> NOTE: You may come across `and` & `or` instructions in the MIPS docs. These are **not what you want!** They are *bitwise operations* which we won't come across for a couple weeks still.

Translating `<cond1> || <cond2>` can be done as follows:
```
if_cond:
    <branch on cond1 being true> if_body
    <branch on cond2 being true> if_body
    b       if_else
if_body:
    # Condition was true
    b       if_end
if_else:
    # Condition was false
if_end:
    # ...
```
> NOTE: you can make this slightly more efficient by swapping the order of the `if_else` and `if_body` sections and getting rid of the `b  if_else` line, but this is only a minor improvement.

Translating `<cond1> && <cond2>` can be done as follows by using the fact that `A && B` is the same as `!A || !B`:
```
if_cond:
    <branch on cond1 being FALSE> if_else
    <branch on cond2 being FALSE> if_else
if_body:
    # Condition was true
    b       if_end
if_else:
    # Condition was false
if_end:
    # ...
```


### Loops in MIPS
Implemented quite similarly to `if(...)` statements using **branches** and **labels**.  
The code structure is much the same, with a conditional branch controlling whether we *enter/exit the loop*.  
The key addition is **another branch at the end of the body** back to the loop condition.  
For loops and while loops are implemented in the same way.

In general, a MIPS loop will looks something like:
```
loop_cond:
    <loop EXIT condition> loop_exit
loop_body:
    <body of the loop>
loop_increment:
    <increment step>
    b       loop_cond
loop_exit:
    <code immediately after the loop>
```

#### A quick example
In C:
```
for (int i = 0; i < 10; i++) {
    // Do stuff
}
// Done
```
In MIPS:
```
    # $t0: i
    li      $t0, 0              # i = 0
loop_cond:
    bge     $t0, 10, loop_exit  # while (i < 10)
loop_body:
    # Do stuff
loop_increment:
    addi    $t0, $t0, 1         # i++
    b       loop_cond
loop_exit:
    # Done
```

### Example: factorial.s
A basic for loop in MIPS.  
Once again, very similar to the example above.