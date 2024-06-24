# Week 5 Tutorial Summary
Welcome to the second (and shortest) part of 1521 - data representation!  
This week we'll be looking at **binary** and **bitwise operations.**

## Bits and Bytes
**Bytes** are a sequence of eight **bits**.  
You may have heard of bits before - they are *the fundamental unit of computing* - or, more literally, **a 1 or a 0.**  
Everything, and I mean everything, in your computer will eventually boil down to a collection of 1s and 0s that **represent a more complex data structure** from things like numbers all the way up to the icon displayed on your screen.

> In the interest of not going on an electrical engineering tangent, that is as deep as we will go in this course.  
> Just know that these bits, these 1s and 0s, are *a representation of hardware concepts* that, despite being very cool, are not very relevant for COMP1521.

Our focus in this tute will be on **how numbers are represented** and **how we can interact with bits directly in C.**

## Binary and Base 2 Numbers
In MIPS, we mentioned how integers were 4 bytes long, now we know what that means!  
Integers are *represented using 4 x 8 = 32 bits* or *a sequence of 32 1s and 0s.*

The question now: **how do 32 1s and 0s represent a number??**

First, a quick detour to primary school...
### Base 10 (Decimal) and Place Value
Hopefully, this is just a quick refresher on the basics of *number systems.*

Our typical number system is called **base 10 (decimal)** because each digit of a base 10 number represents **a power of 10.**  
For example:
```
284 = 200      + 80       + 4
    = 2 * 10^2 + 8 * 10^1 + 4 * 10^0
      ^          ^          ^
      hundreds   tens       ones
```
There are *10 digits* (0 - 9) and, when counting up, you *increment a digit until it reaches the maximum (9) then move on to the next digit* (9 -> 10, 19 -> 20, etc).  

### Base 2 (Binary)
Choosing 10 as the basis for our number system was pretty much based on the number of fingers we had, and is pretty arbitrary.  
Some bases are more useful than others (I personally haven't seen base 7 around too often) but **base 2** (aka **binary**) is ***extremely useful for computing!***  

Why base 2? Because computers only have 1s and 0s!  
So, **computers use a number system that only uses two digits - 0 and 1.**

### Converting Binary to Decimal
Just like base 10, each digit of binary **represents a power of 2.**  
For example:
```
0b1101 = 0b1000  + 0b100   + 0b00    + 0b1
       = 1 * 2^3 + 1 * 2^2 + 0 * 2^1 + 1 * 2^0
```
Breaking down a binary number into powers of two like this makes it really easy to then **convert to decimal** - we just evaluate the powers of two!
```
0b1101 = 1 * 2^3 + 1 * 2^2 + 0 * 2^1 + 1 * 2^0
       = 1 * 8   + 1 * 4   + 0 * 2   + 1 * 1
       = 8       + 4       + 0       + 1
       = 13
```
> NOTE: `0b` is a common prefix for denoting that the following digits are for a **binary** number.  
> Decimal is usually considered the 'default' base so doesn't have a prefix.  
> We will come across a few other prefixes for other bases in a bit...

### Converting Decimal to Binary
There is also a nice trick for converting decimal to binary:

1) Divide the number by 2 repeatedly, keeping track of remainders
2) Stop dividing when you reach 1
3) Starting with a 1 then copying all the remainders in reverse gives you your binary representation

Example:
```
35 -> 17 r1
       8 r1
       4 r0
       2 r0
       1 r0
=> 35 = 0b100011
```

### On Representation vs Value
It is very important to distinguish between numbers with **different values** and numbers with **different bases.**

The base a number is written in *does not change its value!*
It only changes how that number is written - what digits it uses and what those digits mean.  
When a computer stores the binary number `0b1101` using bits, this is **the same** as storing the decimal number `13`.

**Decimal and binary are not different types of numbers!**  
Decimal and binary just present numbers differently - the underlying values are the same.

In practice this means the following two lines of C code **do EXACTLY the same thing!**
```
int x = 13;
int x = 0b1101;
```
> When I say exactly the same thing I mean exactly the same thing!
> There are no exclusive operations or behaviours to defining a number in binary vs decimal.  
> This means **you can use decimal arithmetic on binary values and bitwise operations on decimal values with no problem!**

### Integer Types Revisited
In MIPS, we told you that integers were 4 bytes long (32 bits) and characters were 1 byte long (8 bits).  
This should hopefully make more sense now :)

What should also make sense now is why these types are different:
**they can store different ranges of values!**  
More bits -> digits reach higher powers of 2 -> larger numbers!  

The exact range of each type is not vital knowledge, the important detail is that *the number of bits used by an integer corresponds to the maximum value of a type.*  
Both characters and integers are just *numbers* stored as binary in hardware.
The only difference is **how many bits they have!**

There are some special integer types that **have an exact number of bits** which will be useful for *bitwise operations* when the number of bits we have really matters!

## Other Bases
Some other common bases to see in this course and computing as a whole...

### Hexadecimal
**Hexadecimal (Hex)** is **base 16**.
It uses the digits from 0-9 like base 10 and the first 6 letters of the english alphabet (a, b, c, d, e and f) to make up the remaining 6 digits needed.

Hexadecimal is very common for *large binary numbers* such as *memory addresses* because **one hex digit is equivalent to four binary digits.**  
This means we can use hex as a *more compact way to write binary!*

For example:
```
0x2F = 2 * 16^1 + 15 * 16^0         (F in hex = 15 in dec)
     = 32       + 15
     = 47
    
Or, in binary:
0x2F = 2^5 + 2^3 + 2^2 + 2^1 + 2^0
     = 0b101111
     = 0b 0010 1111
          ^    ^
          0x2  0xF
```
> Note: `0x`, like `0b` for binary, is a common prefix denoting a hexidecimal value.

### Octal
**Octal** is **base 8** and often comes up when talking about *file permissions* which we will cover later in this course.  
It simply uses the digits 0-7.

Similar to hex, octal is often used because it translates to binary well.  
In particular, **one octal digit is equivalent to three binary digits.**

For example:
```
0123 = 1 * 8^2 + 2 * 8^1 + 3 * 8^0
     = 64      + 16      + 3
     = 83

In binary:
0123 = 2^6 + 2^4 + 2^1 + 2^0
     = 0b1001011
     = 0b 001 010 011
          ^   ^   ^
          01  02  03
```
> The prefix for octal is `0`.  
> Yes, really. Just a zero.  
> Fun fact, this means in C, if you write `int i = 0`, that `0` is in octal :)

## Bitwise Operations
**Bitwise operations** are operations, like `+` or `*`, that, rather than operating on the *value* of a variable, operate *directly on the bits of a value.*  
All bitwise operations act on *individual bits.*  
When performing a bitwise operation on or between variables, the **bits of their binary representation are operated on one by one.**  

### List of Bitwise Operations

Bitwise operations can either act on *one variable* like:
- NOT -- `~x`
  - **Inverts** a bit
- Left Shift -- `x << n`
  - **Shuffle bits to the left `n` times**
  - Left most bits get removed
  - Right most bits are padded with 0s
- Right Shift -- `x >> n`
  - **Shuffle bits to the right `n` times**
  - Right most bits get removed
  - Left most bits are padded with 0s*
    - *when using unsigned values (more on this next week)

Or between *two variables* like:
- AND -- `x & y`
  - Checks if two bits are **both 1**
- OR -- `x | y`
  - Checks if **either bit is 1**
- XOR -- `x ^ y`
  - Checks if **one AND ONLY one bit is 1**

#### Example: bitwise.c
A lot of print statements to show off bitwise operations.  
Check out the completed version's comments for some nice worked examples for each bitwise operation :)  
(I could repeat them here but that's kinda redundant)

### Setting and Extracting Bits
A bit is considered **set** when it is **1.**  
A bit is considered **clear** when it is **0.**

So, **setting a bit(s)** means making an individual bit *into a 1 regardless of what it was before.*  
**Extracting a bit(s)** means *clearing all bits except for the bit(s) being extracted.*

To do this, we use a **mask.**  
Masks are a *sequence of bits* (usually we write this in hex so we can more easily see what binary bits are being masked) that we use to *control which bits we set/extract.*  
The general rule for masks is **where there is a 1 in the mask, something happens, where there is a 0, the bit is ignored.**

For example, the mask `0b1001` or `0x9` would be used if you want something to happen to the **1st and 4th bit counting from the right.**

To **set** bits, we **OR** a mask with a value:
```
Use mask 0b1001 to set the 1st and 4th bits of 0b1100:
0b1100 | 0b1001 -> 0b1100
value  | mask      0b1001 OR
                   ------
                   0b1101
                     ^  ^ bits set
                      ^^  bits ignored

```

To **extract** bits, we **AND** a mask with a value:
```
Use mask 0b1001 to extract the 1st and 4th bits of 0b1100:
0b1100 & 0b1001 -> 0b1100
value  & mask      0b1001 AND
                   ------
                   0b1000
                     ^  ^ bits extracted
                      ^^  bits cleared (ignored)

```

### Creating Masks
Two common ways to make masks:
1) Use a constant (e.g. `uint32_t mask = 0x9`)
    - Common for more complex masks
    - Super easy
2) Define the width of the mask using a constant then shift it into position
    - Often used for variable masks
    - More difficult to make
    - E.g. `uint32_t mask = 0b111 << 4` creates a mask that covers bits 4-6 counting from the right

> **ALWAYS use an unsigned (uintXX_t) type for masks!**  
> You often bit shift masks and, as implied earlier, right shifting in particular (but left shifting too!) can **break your program if the mask is signed!!**

#### Example: reverse_bits.c
We use bitwise operations here to reverse the bits of a number.  
We do this by extracting the right most bit of the original number and setting the left most bit of a new reversed value if that bit was set.  
Working our way right to left in the original value's bits and left to right in the new value's bits eventually reverses the original bits!

### (Bonus) Advanced Bitwise Operations
These are bitwise operations like setting and clearing that you won't need to use at all, or at least not nearly as often.

#### Toggling
You can toggle bits using a mask and **XOR**:
```
Use mask 0b1001 to toggle the 1st and 4th bits of 0b1100:
0b1100 ^ 0b1001 -> 0b1100
value  ^ mask      0b1001 XOR
                   ------
                   0b0101
                     ^  ^ bits toggled
                      ^^  bits ignored

```

#### Clearing
You can clear bits using an **inverted mask (`~mask`)** and **AND**:
```
Use mask 0b1001 to clear the 1st and 4th bits of 0b1100:
0b1100 & ~0b1001 -> 0b1100
value  & ~mask      0b0110 AND
                    ------
                    0b0100
                      ^  ^ bits cleared
                       ^^  bits ignored
```

## Sidenotes: Endianness and Significant Bits
### Significant bits
Often you will hear about **most significant** or **least significant** bits, often abbreviated as **MSB** and **LSB** respectively.  
These are referring to the bits representing the **largest powers of 2** (the *left-most bits*) and the **smallest powers of 2** (the *right-most bits*) respectively.

Example:
```
0b111000101010100101
  ^                ^
 MSB              LSB
```

### Endianness
Consider the common case of storing multiple bytes (e.g. the 4 bytes of an integer) in memory.  
Each memory address is *one byte* large, but you have *multiple bytes to store.*  
There is a choice: **what order do you store the bytes in?**

**Big endian** -- *Most significant byte* first.  
E.g.
```
0x12345678
Dividing into bytes (2 hex digits = 8 bits):
0x 12 34 56 78
In memory:
|12|34|56|78|
```
**Little endian** -- *Least significant byte* first.  
E.g.
```
0x12345678
Dividing into bytes:
0x 12 34 56 78
In memory:
|78|56|34|12|
```
> Note that **only the order of bytes change!**  
> The *bits within the bytes remain the same.*

As strange as it may at first seem, **little endian is the default for most systems.**

Endianess often comes up when *reading values from a file one byte at a time!*  
Make sure you read bytes individually and use bitwise operations (shifting and setting) to reassemble any multi-byte values you read in!