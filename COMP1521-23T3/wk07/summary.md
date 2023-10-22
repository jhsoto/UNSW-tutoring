# Week 7 Tutorial Summary
Hope you liked bits, because this week we've got more of them!
We're looking at **negatives** and **floating points**.

## Negative Numbers
Last week we introduced the concept of binary numbers and base-2.  
An issue with this system as we explained it is that we can only represent positive values!

They are actually a lot of different ways to represent negative numbers, some less common ones you might see around are:

#### Sign-Magnitude Numbers
This is the simplest way to do negatives is to include a *sign bit*.  
What this means is that the **most significant bit will determine if our value is positive or negative**.
This is the *sign*.  
If it is `0`, the number is *positive*.  
If it is `1`, the number is *negative*.

> **NOTE:** Having a sign bit in some form is actually really desirable since it makes it really easy to determine whether a number is negative or not!  
> You'll find that most (but not all) negative formats include a sign bit somehow.

The **remaining bits are normal base-2**.
This is the *magnitude*.

For example:
```
Using 8 bit numbers:
 21 = 0b 0 0010101
-21 = 0b 1 0010101
         ^ ^
         | Magnitude: 21 using 7 bits
         Sign
```

#### Biased Numbers
This is a more complicated (but important) way to represent negatives.

We introduce a **bias** to our numbers.  
This bias will serve as a *constant offset* to whatever our value would normally be.  
One way to think of it is it's shifting the zero-point in our base-2 format.

Usually, the bias will be chosen to be *half the maximum unsigned value* that can be stored in a given number.  
For an 8-bit number with an unsigned range of `0 <-> 255`, the bias would usually be `127`.  
This would mean our biased numbers would have a range of `-127 <-> 128 `.

For example:
```
For 8-bit numbers and an offset of 127:
  0 = 0b 01111111   (127)
 21 = 0b 10010100   (148)
-21 = 0b 01101010   (106)
         ^           ^
         |           unsigned conversion of bits
         biased base-2 representation
```

#### Bitwise NOT (One's Complement)
Another pretty simple way to do negatives is to **take the bitwise NOT** of a value.

For example:
```
  0 = 0b 00000000
 -0 = 0b 11111111    (this is not ideal!)
 21 = 0b 00010100
-21 = 0b 11101011
```

### Two's Complement
The standard negative format for binary numbers is **two's complement.**  
By definition, two's complement is the **bitwise NOT of a value plus one.**

An easier way to take the two's complement is as follows:
1) Start from the LSB
2) Step left through the bits until there is a  '`1`' bit
3) Flip every bit to the left of that first '`1`' bit

For example:
```
 20 = 0b 00010100
-20 = ~0b00010100 + 1
    = 0b 11101011 + 1
-20 = 0b 11101100

Or using the other method:
 20 = 0b 00010 100
-20 = 0b 11101 100
 flipped ----< >-- left the same
```

#### Why Two's Complement??
Some key advantages of two's complement:
- Has a sign bit (the MSB)
- Easy to implement in hardware
- With two's complement, a hardware addition circuit **also performs subtraction** (adding negatives) without any modification!

### Value range using negatives
A key fact when working with negatives is that **you will always be limited to at most half of the range of unsigned values** when working with signed (negative) values.  
With a given number of bits, you can only store a fixed amount of data.  
*No matter how you do negatives, you will always need to replace some positive numbers to store them.*

For example:
```
Using two's complement:
uint8_t range:    0 <-> 255
 int8_t range: -128 <-> 127
```

## Floating Point and Fractional Numbers
**Floating point or fractional numbers** (like 1.25 or 0.034) are numbers with a *decimal point.*  
Representing these in binary is a real challenge, and the standard format we use is quite complex.

We'll start off with a simple extension of binary numbers:

### Binary with a Decimal Point
First let's just clarify what a binary number with a decimal point looks like and how it works.

In base-10, digits after the decimal point represent *negative powers of 10.*  
For example:
```
1.25 = 1        + 0.2       + 0.05
     = 1 * 10^0 + 2 * 10^-1 + 5 * 10^-2
```
The same idea applies in binary: **binary digits after the decimal point represent negative powers of 2.**  
For example:
```
0b1.101 = 1 * 2^0 + 1 * 2^-1 + 0 * 2^-2 + 1 * 2^-3
        = 1       + 0.5      + 0        + 0.125
        = 1.625
```

#### Converting from Decimal to Binary Part 2
You might remember a trick from the last tute for converting from decimal to binary for integers.  
This still applies to binary numbers with a decimal point, but we need a new trick for **converting the fractional part to binary:**
1) Multiply the fractional part by 2 repeatedly,
ignoring (but keeping track of!) the integer parts of the results
2) Stop multiplying when you reach '`1.0`'
3) Starting from the first result and working down, the *integer parts* (which should be either `0` or `1`) give your binary number

For exmaple:
```
0.8125 -> 1.625
          1.25    (only multiplying 0.625)
          0.5     (only multiplying 0.25)
          1.0
=> 0.8125 = 0b0.1101
```

#### A Problem with Converting to Binary
**Not every base-10 number can be exactly converted into binary!**
For example:
```
Applying the above trick to 0.1
0.1 -> 0.2
       0.4
       0.8
       1.6
       1.2
       0.4
       0.8
       1.6
       1.2
       ...
=> 0.1 = 0b000110011...
```
We have an infinite series of bits!  
This is simply a limitation of binary numbers and is not something we can just fix.  
It's similar to how values like 1/3 in base-10 need infinite digits to write out with a decimal point.

### Fixed Point Numbers
Just introducing the idea of the decimal point does not quite give us a complete representation for fractional numbers.  
Say, for instance, the following 8-bits: `0b11001000`, are meant to represent a fractional number.
*Where is the decimal point?*  
*There is no way to know!*

We can solve this by **fixing the decimal point in place** after a specific number of bits, often the halfway point.  
That way, we always know where the decimal point is.

For example:
```
8-bits with the decimal point in the middle (after 4 bits):
0b11001000 -> 0b1100.1000
            = 8 + 4 + 0.5
            = 12.5
```
One major issue with this format is that **there is a tradeoff between the size of the integer and fractional parts.**  
This means if you want to store large integers, you have to be happy with small (less precise) fractional parts and vice versa.

It would be nice if there was a format that nicely handled both very large and very small numbers...

### Scientific Notation
Base-10 already has a format for nicely handling very large and very small numbers: **scientific notation!**

A quick refresher/intro: scientific notation involves *multiplying/dividing a number by 10 repeatedly* until there is exactly *one non-zero digit to the left of the decimal point.*  
To make sure the actual value isn't changed, we also need to *multiply by a power of 10 to cancel all the previous shifting/multiplying.*  
For example:
```
307.3
 -> Divide by 100 to get 3.073  (One digit before decimal point)
 -> Add on '* 10^2' to cancel the division by 100 (still want it to equal 307.3)

=> 307.3 = 3.073 * 10^2   in scientific notation
```
> You may notice that this looks a bit like shifting a binary number...  
> Shifting a base-10 number left is the same as multiplying by 10.
> Shifting a base-10 number right is the same as dividing by 10.  
> By extension, **a binary left shift multiplies by 2** and **a binary right shift divides by 2!**  
> Sometimes you will see shifting operations being used as a fast alternative to multiplying.


### Floating Point Numbers
As always, we can apply scientific notation to binary numbers to get closer to what we call **floating point numbers.**  
The main difference as usual is swapping the multiplying and dividing by 10 for multplying and dividing by 2.

For example:
```
0b1100.1000
 -> Shift right by 3 places to get 0b1.1001000 (dividing by 2^3)
 -> Add on `* 2^3` to cancel the division

=> 0b1100.1000 = 1.1001 * 2^3 in scientific notation
```

### The Floating Point Standard Format (IEEE754)
Now we finally get to the actual floating point format we use all over the place for our fracrional numbers: **IEEE754!**

It basically takes the floating point scientific notation format we just used and extracts all the important information *with some clever tricks added in!*

The 32-bit version of the format looks like this:
![floating point format](https://media.geeksforgeeks.org/wp-content/uploads/Single-Precision-IEEE-754-Floating-Point-Standard.jpg)

Let's take a look at what each of these components are and any tricks they use:

#### Sign
A simple sign bit.  
0 for positive, 1 for negative.  
No tricks here :)

#### Exponent
The exponent of the power of two we used to cancel out the shifting we did to get the number into scientific notation.

For example:
```
0b1100.1000 = 1.1001 * 2^3
                         ^ the exponent
```

We would like to support both **positive and negative exponents** which means we need to choose a negative number format to use.  
The standard chose to use a **biased negative number** with a **bias of 127.**

For example:
```
The exponent '3' from above using a biased 8-bit representation:

3 = 0b00000011  (no bias)
 -> 0b10000010  (with bias of 127)
```

#### Mantissa
The *fractional part* of the number in scientific notation.  
More simply: the part after the decimal point.

For example:
```
0b1100.1000 = 1.1001 * 2^3
                ^--^ the mantissa
```
You may notice this means the '`1`' before the decimal point is entirely excluded from the bits used in the final format.
This is intentional!  
Remember that in scientific notation the first digit *cannot be zero.*  
In binary, there is *only one other digit this could be!*  
This means, **all binary numbers in scientific notation start with a '`1`',** so this bit is left out of the format.

#### An example translation
A quick example of going from decimal to floating point and back again...
```
Using the number 3.375

First we convert to binary including the decimal point:
3.375 = 2 + 1 + 0.25 + 0.125    (sum of powers of two)
      = 0b11.011

Then we convert to scientific notation:
0b11.011 = 1.1011 * 2^1

Then extract the needed components:
Sign -> positive -> 0b0
Exponent -> 1 (unbiased) -> 128 = 0b10000000 (biased)
Mantissa -> 0b1011 (without padding)

Put it all together!
3.375 =
    0b 0 10000000 10110000000000000000000
```

```
Going the other way...
0b11000000101110000000000000000000

Split into components:
0b 1 10000001 01110000000000000000000
   ^ ^------^ ^---------------------^
sign exponent        mantissa

Sign -> 0b1 -> negative
Exponent -> 0b10000001 = 129 (biased) -> 2 (unbiased)
Mantissa -> 0b0111 (without padding)

Assemble components into scientific notation:
- 0b1.0111 * 2^2
^     ^--^     ^
sign mantissa exponent

Evaluate back into decimal!
- 0b1.0111 * 2^2 = - 0b101.11   ('* 2^2' <=> left shift by 2)
                 = - (4 + 1 + 0.5 + 0.25)
                 = -5.75

All together...
0b11000000101110000000000000000000
    = -5.75
```

#### Special Values
The IEEE754 format also includes some special values which are represented by specific parts of the format matching special bit patterns:

| Special Value | Sign | Exponent      | Mantissa |
|---------------|------|---------------|----------|
| NaN           | Any  | 255 (All `1`) | Non-zero |
| +Inf          | 0    | 255 (All `1`) | 0        |
| -Inf          | 1    | 255 (All `1`) | 0        |
| Zero          | Any  | 0             | 0        |
| Subnormal     | Any  | 0             | Non-zero |

> Subnormal numbers are really, really weird and are **not part of the course.**  
> Feel free to ignore them entirely.  
> Also don't ask me about them please I don't know how they work either...

#### A Note on Precision
The floating point format can store really large and really small numbers.  
Obviously, it isn't able to store all possible values, its still only a 32-bit format!  
There are a *limited number of possible values a float can take,* and thus **the precision of large and small numbers is very limited!**

We only have 23 mantissa bits, we can't store anything to more than 23 binary decimal places in scientific notation.  
That means, even though we can store numbers larger than we can in a regular 32-bit integer, they **won't be exact!**  
This leads to some odd behaviour especially with large numbers and numbers that can't be cleanly converted into binary like `0.1`.

## Extra Bitwise Example - middle_6.c
An example showing the extraction of the middle 6 bits of a 32 bit value.
