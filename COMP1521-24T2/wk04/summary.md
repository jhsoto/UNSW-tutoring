# Week 4 Tutorial Summary
This week is the last week of MIPS!  
We cover **2D arrays and functions**.  
These are the most complicated MIPS topics we cover!


## MIPS 2D Arrays
2D arrays are stored in memory much like 1D arrays.  
Often you think about 2D arrays as *grids with rows and columns*,
but in MIPS this doesn't hold up.  
Memory is **1 dimensional**, there is no concept of rows and columns!

### 2D Array Memory Layout

Instead, a 2D array is represented by **placing all the rows of the grid sequentially in memory**.

For example:
> A B C  
> D E F  
> G H I  

Becomes:
> A B C D E F G H I

A nicer way to think about 2D arrays then is as **an array where each item is also an array**.  
Using the above example:
> | A B C | D E F | G H I |  

Here, we separate the 2D into 3 smaller arrays, the first containing 'A B C', the next 'D E F' and the last 'G H I'.

If we now name the arrays...  
> | array1 | array2 | array3 |  

This looks a lot like a 1D array again!

### 2D Array Access Formula
We can come up with a formula for 2D array access by breaking the process into two steps:

1) **Get to the correct row**  
-> skipping past whole arrays
2) **Get to the correct column**  
-> a normal 1D array access!

Let's say we want to access `array[row][col]`
where our array is defined like 
`int array[N_ROWS][N_COLS]`.  

First, we need to get to the correct row.  
Thinking of our 2D array as *an array of arrays*, we can adapt our 1D array formula to give us:
```
array + 4 * N_COLS * row
```
Where we are *skipping past `row` items* each of which are *`4 * N_COLS` bytes large*.  
The size of each item comes from the fact that **each row (an array itself) has `N_COLS` items each of which are `4` bytes large**, giving a total size of `4 * N_COLS` bytes per array.

> NOTE: Be very careful with `N_COLS` vs `N_ROWS`!  
> We are skipping past rows, so it might seem like `N_ROWS` is what we should use here.  
> **DO NOT USE `N_ROWS`**  
> Each row consists of `N_COLS` columns, which is how large the actual row array is and thus is what we actually want.  

The above formula will **get us the correct row**, which we could also think of as **the correct array in our 2D array**.

From here, we just need to apply the 1D array formula, giving us:
```
(array + 4 * N_COLS * row) + 4 * col
```
Where *`array + 4 * N_COLS * row` is the starting address of the row (1D array)* we are accessing and *`4 * col` is the number of bytes we are skipping past* within that array to reach the correct column.

Doing some factorising and generalising to all array types, we get the formula:
```
&array[row][col] = array + (N_COLS * row + col) * (size of an array element in bytes)
```
Notice that `N_COLS * row + col` is the **total number of array items we need to skip past** to reach the target row and column.

In MIPS code, a 2D array access, with `$t0 = row` and `$t1 = col`, assuming an array of integers, looks like:
```
        li      $t2, array
        mul     $t3, $t0, N_COLS    # row * N_COLS
        add     $t3, $t3, $t1       # row * N_COLS + col
        mul     $t3, $t3, 4         # (row * N_COLS + col) * 4
                                    # '4' since integers are 4 bytes
        add     $t2, $t2, $t3       # array + (row * N_COLS + col) * 4
                                    # $t2 = &array[row][col]
        lw      $t3, ($t2)
```

#### Example: flag.s
A fairly standard 2D array access is the core of this example.  
Just use the formula :)  
The one trick here is that we have an array of **characters**, meaning each array item is only **1 byte** large.

## MIPS Functions
MIPS does not have the concept of functions like C does.  
Instead, we must write MIPS code that recreates what we want functions to be able to do from scratch.

### Calling Functions in MIPS
The first thing we want to do is be able to call a function.  
There are 3 steps to calling a MIPS function:

1) Load arguments into **argument registers (`$a0` - `$a3`)**  
    In code: `li      $a0, 1`

2) **Jump and link** to the label located at the *start of the function*.  
    In code: `jal    my_func`  
>    `jal` (jump and link) is an instruction which jumps (branches) to a label **and sets `$ra` to point to the next instruction after the `jal`**.  
>    `$ra` is the **return address** register and tracks which instruction to execute next when returning from a function.
> In combination with the `jr` instruction, which jumps to the location stored in a register, we can return from functions like so:
> `jr $ra`

3) Retrieve return value from `$v0`

In all, translating `x = my_func(1)` to MIPS looks like:
```
        li      $a0, 1
        jal     my_func
        move    $t0, $v0        # $t0 = x
```

#### Example: add2.s
A basic function calling exercise.  
We actually need to preserve `$ra` here using `push` and `pop` for reasons we will cover here in just a minute...

### MIPS Function Calling Convention (a.k.a ABI)
An important note with calling functions is that **there is nothing special about `$a` or `$v`** that mean we have to use them for function calls.  
Instead, MIPS programmers *code according to an agreed set of standards* so everyone's code can call functions correctly.  
These are what we call the **MIPS ABI** or **function calling conventions**.

Here are the key conventions/rules for MIPS functions:
- Use **`$a`** registers for **arguments**
- Use **`$v`** registers for **return values**
- Assume that **`$t`** registers have their values **clobbered (or overwritten)** by calling a function
> Remember that MIPS only has one set of registers, if you use `$t0` in two functions, that is **the same `$t0`** and the two functions *can affect each other!*
- It is guaranteed that **`$s`** registers **will not be clobbered** by calling a function

> NOTE: Breaking these rules *will not always cause your code to break*.  
> Autotests, particularly in the assignment, may not check you follow all these rules, but **the assignment marking will add specific tests** (the strict tests) **that will specifically check these rules!** Be careful!

### Writing a MIPS Function
With the ABI in mind, we can write a MIPS function just like a normal MIPS program but with a few extra considerations:

1) We are given arguments in the `$a` registers
2) We have to place the function return value in `$v0` before we return
3) We have to return from the function using `jr $ra`
4) We have to *preserve the intial values in `$s` registers* so they appear unchanged when we return

The first two considerations are pretty simple, but the last two are a bit more difficult (the third for a subtle reason!)

### Preserving Values and the Stack
There are a few key registers that our function may want to modify but **the ABI/functionality of our code depends on them not being changed.**  
The obvious registers this applies to are the `$s` registers, but this actually applies to `$ra` as well!

> The reason we have to preserve `$ra` is because of `jal`.  
> If our function calls another function, the `jal` we use to call that function will **replace our original `$ra` value**, *preventing us from correctly returning from our function!*

We can preserve the values by storing them in a safe place - **the stack!**

There is a register in MIPS, `$sp`, the *stack pointer*, which points the to **the bottom most item on the stack in memory**.  
Recall that the stack is the section of memory at the very top, the very highest addresses.  
The stack pointer starts at the very top of the stack and slowly moves down through address as items are added to the stack.

We can **push** items onto the stack by *moving the stack pointer down and storing a value where the stack pointer points to*.  
This places values in memory where they are safe from modification!  

Similarly, we can **pop** items from the stack by *loading the value stored where the stack pointer points to and move the stack pointer up.*  
This restores the value we saved when we pushed earlier!

You can do this manually by adding/subtracting from `$sp` and using `lw/sw` but MIPSY adds extra instructions, `push` and `pop` which do all the stack work for you!

Putting this all together, we can preserve a register value in functions like so:
```
my_func:
my_func__prologue:
        push        $ra     # Save $ra on the stack
my_func__body:
        # Do stuff...
my_func__epilogue:
        pop         $ra     # Restore the old $ra value
        jr          $ra     # Return!
```

> NOTE: It is **extremely important** to pop in the **opposite order** to how you pushed!  
> Remember the stack pointer points at the *most recent thing you added*, so **the first thing you pop is always the last thing you pushed.**

### When to use `$s`? When to Push and Pop?
Knowing when to use a `$s` register and when you need to push and pop are **vital for following the MIPS ABI!**

#### Question: Do I need to use an `$s` register?
If you want to store a value in a register, ask yourself these 3 questions:

1) Am I using this register and its value **before a function call?**
2) Am I using this register **after a function call?** 
3) Do I need the register to **stay the same before and after the function call?**

If you answered **YES** to *ALL 3*: **use an `$s` register.**  
If you answered **NO** to *ANY*: **use a `$t` register.**  

`$t` registers should be you go-to register still, only use `$s` if you have to!

#### Question: Do I need to push/pop a register?
This question is a lot simpler:

Did you *use an `$s` register?*  
If YES -> You have to **push/pop that `$s` register.**

Did you *call another function?*  
If YES -> You have to **push/pop `$ra`.**

That's it. **You should never push/pop registers other than `$s` registers and `$ra`!!**

#### Example: add4.s
A more complex function example where we have to use some `$s` registers.

## MIPS Style
The key features of MIPS style are:

### Function comments
These come in a standard format at the top of every function you write:
```
	# Args:     void
	#
	# Returns:  void
	#
	# Frame:    [...]
	# Uses:     [...]
	# Clobbers: [...]
	#
	# Locals:
	#   - $t0: int result
	#
	# Structure:
	#   main
	#   -> [prologue]
	#       -> body
	#   -> [epilogue]
```
Here's a breakdown of what to include in each section:
- *Args:* argument types + names and **what register they are passed in**
- *Returns:* what **type** the return value is
- *Frame:* list all registers you **pushed/popped**
- *Uses:* list all registers you **used**  
This should include `$t` and `$s` registers at minimum, it's best to include `$a` and `$v` registers as well.
- *Clobbers:* list all registers you **used but didn't push/pop**  
The same as *Frame - Uses*
- *Locals:* brief descriptions of **how the `$t` and `$s` registers you used were utilised**  
The easiest thing to put here is **a C variable declaration** if possible
- *Structure:* a list of all the **labels** used by your function  
Optionally, you can indent the labels here to represent control structures like loops/ifs

An example function comment (from `add4.s`) is:
```
	# Args:
	#	- $a0: int a
	#	- $a1: int b
	#	- $a2: int c
	#	- $a3: int d
	#
	# Returns:
	#	- $v0: int
	#
	# Frame:    [$ra, $s0, $s1, $s2]
	# Uses:     [$a0, $a1, $v0, $s0, $s1, $s2]
	# Clobbers: [$a0, $a1, $v0]
	#
	# Locals:
	#	- $s0: Save 'c' ($a2)
	#	- $s1: Save 'd' ($a3)
	#	- $s2: int res1
	#
	# Structure:
	#   add4
	#   -> [prologue]
	#       -> body
	#   -> [epilogue]
```

### Indentation
In MIPS, please use **8-width tabs** for indentation.  
The general rules for indentation are:
- Do not indent labels
- Indent instructions by one tab
- Indent between an instruction and the register arguments
- Indent before comments such that **all comments in a function line up with each other**

An example of good indentation:
```
label:
        li      $a0, 1                      # line up
        b       really_long_label_name      # comments!
```

An example of bad indentation:
```
        label:
        li      $a0, 1      # line up
        b really_long_label_name     # comments!
```

> NOTE: This may leave with some long lines, especially including comments.  
> This is okay! Long lines in MIPS are not harshly penalised.  

### Commenting
Make sure to comment your MIPS code!  
MIPS is hard to read on its own so comments are vital.

The easiest way to comment your code is by **putting the C code you are translating next to the MIPS code that translates it.**  
You can also provide **equivalent descriptions** of what the code is doing.

The tutorial code in this repo (should) be a great example of good commenting :)

### Label Names
**Make sure your label names are descriptive!!**  
Avoid labels like `if1:` or `loop1:` as these are:
- Not descriptive
- Make it more likely you accidentally duplicate label names
- Make your code harder to understand when you branch to them

**Long labels are good!** The more descriptive the better.  
Obviously a 100 character label is bad but don't try to shorten labels for the sake of shortening them.

The last point with labels is to **prefix your labels with the name of the function.**  
The starter code should do this already, so just keep it up!  
A prefix for a function called `my_func` would be `my_func__`.

An example of a good label name:
```
my_func__row_loop_condition
```
Some examples of bad label names:
```
if1:
main__loop:
check_condition:
```

### A final note on style...
Some of these rules may seem strict, but some parts of this are just *my preferences.*  
If you prefer a different **but equally sensible** variation on some of the style choices outlined above, that's fine!  
Tha main thing with style is **BE CONSISTENT!!**  
It's super easy to spot an inconcsistency when marking and consistency is ultimately what we care about most!