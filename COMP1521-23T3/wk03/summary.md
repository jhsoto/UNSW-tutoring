# Week 3 Tutorial Summary

The focus of this week's tutorial was how we **can work with memory using MIPS**.  
In particular, we focus on *arrays* and *structs* this week.

## Accessing Memory in MIPS
First a quick note on what is meant by 'memory'.  
*Memory* is referring to *RAM* and the various *segments* it is divided into.
Recall the **text, data, heap and stack** sections we talked about in week 1!  

This week, we will be looking at using the **data** section primarily.  
> Note: We have already been using the **text** segment!  
> Remeber that the **text** segment is where our code resides in memory.  
> So far, all the MIPS code we have written has been stored in the **text** segment while executing!


### Memory Access Instructions
All memory access instructions in MIPS use *labels* as 'pointers' or **memory addresses** to know what part of memory to load/store information from.  
The main instructions we use are:

* `lw <register>, (<address>)`  
loads *4 bytes* (aka a **word**) from memory into a register

* `lb <register>, (<address>)`  
loads *1 byte* from memory into a register

* `sw <register>, (<address>)`  
stores *4 bytes* from a register into memory

* `sb <register>, (<address>)`  
stores *1 byte* from a register into memory

#### Typical Load/Store Structure
A typical load from memory would look something like the following:
```
la      $t0, my_label
lw      $t1, ($t0)
```
This would load 4 bytes from the memory located at the label `my_label` into `$t1`.

#### Alternative load/store syntax
There is also an alternative syntax for loading/storing that lets you add a **constant byte offset** to the address you are accessing.  
This syntax looks like the following for a *4 byte additional offset*:
```
lw      $t1, 4($t0)
```
> Note: The additional offset **must be an immediate (constant number)** and the value in the brackets **must be a register**.  

> On a similar note, you can only store values into memory **from a register**. You can't store an immediate value in memory directly.  
`sw   0, ($t0)` -- Does not work  
`sw $t1, ($t0)` -- Does work

### Example: global_variable.s
Global variables are the simplest use of memory in MIPS.
Recall that global variables are stored in the **data** segment of memory.

A global variable in MIPS then just involves us placing (in our example), the integer `10` in the data segment using `.word 10` (more on what this is in a sec!).  
Then we can use `lw` and `sw` to modify the global variable.

> Be careful with modifying global variables!
> Make sure you **store the modified variable back into memory using `sw`!**  
> If you forget this, *only the copy you would have loaded into a register will have changed.*


## Data Directives
MIPS lets us directly control memory while writing our code using [**data directives**](https://elgar.cse.unsw.edu.au/~cs1521/23T3/resources/mips-guide.html#directives).  
These let us place various types of data in certain segments of memory.

The main directives we will use are:
* `.text`  
Indicates that the following code/data should go in the **text segment**

* `.data`  
Indicates that the following data should go in the **data segment**

* `.word`  
Places a given list of *4 byte* values sequentially in memory

* `.byte`  
Places a given list of *1 byte* values sequentially in memory

* `.space n`  
Reserves `n` bytes as *uninitialised memory*

* `.align n` (advanced topic)  
Adds padding zeroes to the memory so that the next directive can place its data on a *2^n byte boundary.*  
This is important to prevent **unaligned memory accesses** (usually a `lw` or `sw` on an address which is not a multiple of 4) which are not allowed!

### Example: memory.s
A quick look at using memory directives and various strange load/store behaviours.


## Arrays in MIPS
To use arrays in MIPS we need to properly understand what an array looks like in memory.  
You may have heard before that an array is **a list of numbers stored sequentially in memory**, and this exactly what is going on.

### How Arrays Are Stored In Memory
When we have an array, let's say `arr = [1, 2, 3]` for example, our array starts at some memory address, let's say `0x100`.  
The number `1`, which is `arr[0]`, is stored at this starting address `0x100`.

The next number, `2` or `arr[1]`, is stored immediately afterwards at the address `0x104`.  
But wait - isn't that 4 addresses after? Yes it is! But, integers take up **4 bytes of space** and each memory address **refers to 1 byte**.   
So, our number `1` really exists from address `0x100` to `0x103` inclusive!

Similarly, the final number, `3` is stored at the address `0x108`.

### Accessing Arrays in MIPS
How do we use this information in MIPS?
Remember that `lw` and `sw` use **memory addresses** to determine where to load/store from.  
This means to use arrays, we need to be able to *calculate the memory address of each array element*.  
Using what we just discussed about how arrays are stored in memory, we can come up with a little formula:
```
&array[i] = &array + i * (size of array elements in bytes)
```
Let's break this down a little:

- `&array[i]` is the memory address of the ith element of our array.  
This is what we want to use as the address for `lw` and `sw`.

- `&array` is the starting address of our array.  
In MIPS, this is a **label** we use to refer to our array.

- `i * (size of array elements in bytes)` describes how many bytes *we skip past to reach the ith element* of our array.  
We skip past `i` items each of which are some number of bytes large (e.g. 4 for integers)

A typical MIPS array access then looks something like this, where `$t0 = i`:
```
la      $t1, array          # $t1 = &array
mul     $t2, $t0, 4         # For an array of integers
add     $t2, $t2, $t1       # $t2 = &array + i * 4
lw      $t3, ($t2)          # $t3 = array[i]
```

### Example: remove_negatives.s
A reasonably basic array exercise where we read/write to an array to replace any negative numbers in it with zereos.


## Structs in MIPS
Structs are actually quite similar to arrays in MIPS.  
The key difference is that where *all items in an array are the same size*, **the items in a struct can be of varying sizes.**

### How Structs Are Stored In Memory
Just like arrays, all the data in a struct is stored **sequentially in memory**.  
This means that the first field of struct is stored at the *starting address* and the second field is stored *directly after the end of the first item*.

Take for example the following C struct:
```
struct my_struct {
    int x;
    char y;
}
```
If the struct starts at address `0x100`, then `my_struct.x` would be stored at address `0x100`.  
Remembering that integers are *4 bytes* long, this means the next available memory location is `0x104`, and so `my_struct.y` would be stored at `0x104`.

> Note (**advanced topic**): Since structs can contain mixes of data types, they often require `.align` directives **before** and sometimes **in the middle** of the struct.  
> For example, if we swap the order of `x` and `y` in the previous struct definition, we would need a `.align 2` before `x` so that loading/storing from it remains aligned.  
> In this case, `my_struct.y` is stored at address `0x100` and `my_struct.x` is stored at `0x104`. 
> The memory from `0x101` to `0x103` is filled with padding by `.align 2`.

### Accessing Structs in MIPS
Structs are simpler to access in MIPS than arrays, we just need to know how many bytes to *skip past from the start of the struct* in order to access the correct field.

Using the same struct from before, we could access the `x` field like so:
```
la      $t0, my_struct
lw      $t1, ($t0)          # $t1 = my_struct.x
```
And we could access the `y` field like so:
```
la      $t0, my_struct
lb      $t1, 4($t0)         # $t1 = my_struct.y
```
> Note the use of `lb` when accessing `my_struct.y`. 
> Always make sure you are using the **correct load/store instruction** to *match the size of the data you are accessing*!!!
