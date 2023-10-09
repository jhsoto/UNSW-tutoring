// Program to demonstrate a few bitwise operations!
// Comment/uncomment each printf to see what happens.

#include <stdio.h>
#include <stdint.h>     // This adds all the fixed-sized integer defintions

int main() {
    // Always use UNSIGNED integers when working with bitwise operations
    // Signed integers have strange behaviour when being right shifted (more on why next time!)
    uint16_t a = 0x5555; // = 0b 0101 0101 0101 0101
    uint16_t b = 0xAA55; // = 0b 1010 1010 1010 1010
    uint16_t c = 0x0101; // = 0b 0000 0001 0000 0001

    // Quick note on the printf format used here:
    // %04x
    //  ^   pad with zeroes
    //   ^  pad until result is at least 4 characters long
    //    ^ print value in hexadecimal

    // OR
    printf("a | b  = 0x%04x\n", a | b);

    // AND
    // printf("a & b  = 0x%04x\n", a & b);

    // XOR
    // printf("a ^ b  = 0x%04x\n", a ^ b);

    // AND + NOT
    // printf("a & ~b = 0x%04x\n", a & ~b);

    // Left shift
    // printf("c << 6 = 0x%04x\n", c << 6);

    // Right shift
    // printf("a >> 4 = 0x%04x\n", a >> 4);
    /*
    Which of the following is the correct value of a >> 4?
    A) 0b 0101 0101 0101 0101 = 0xAAAA
    B) 0b 0000 0101 0101 0101 = 0x0AAA
    C) 0b 1111 0101 0101 0101 = 0xFAAA
    */
}
