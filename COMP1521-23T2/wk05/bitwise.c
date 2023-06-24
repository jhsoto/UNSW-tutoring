// Program to demonstrate a few bitwise operations!
// Comment/uncomment each printf to see what happens.

#include <stdio.h>
#include <stdint.h>     // This adds all the fixed-sized integer defintions

int main() {
    // Always use UNSIGNED integers when working with bitwise operations
    // Signed integers have strange behaviour when being right shifted (more on why next time!)
    uint16_t a = 0x5555;
    // 0b 0101 0101 0101 0101
    uint16_t b = 0xAA55;
    // 0b 1010 1010 0101 0101
    uint16_t c = 0x0001;
    // 0b 0000 0000 0000 0001

    // Quick note on the printf format used here:
    // %04x
    //  ^   pad with zeroes
    //   ^  pad until result is at least 4 characters long
    //    ^ print value in hexadecimal

    // OR
    printf("a | b  = 0x%04x\n", a | b);
    // a - 0b 0101 0101 0101 0101
    // b - 0b 1010 1010 0101 0101  OR     - 1 if EITHER bit is 1, else 0
    //  -> 0b 1111 1111 0101 0101
    //     0x F    F    5    5
    //  -> 0x FF55

    // AND
    printf("a & b  = 0x%04x\n", a & b);
    // a - 0b 0101 0101 0101 0101
    // b - 0b 1010 1010 0101 0101  AND    - 1 if BOTH bits are 1, else 0
    //  -> 0b 0000 0000 0101 0101
    //     0x 0055

    // XOR - exclusive or
    printf("a ^ b  = 0x%04x\n", a ^ b);
    // a - 0b 0101 0101 0101 0101
    // b - 0b 1010 1010 0101 0101  XOR    - 1 if exactly one of the bits are 1 (EITHER but NOT BOTH), else 0
    //  -> 0b 1111 1111 0000 0000
    //     0x FF00

    // AND + NOT
    printf("a & ~b = 0x%04x\n", a & ~b);
    //  a - 0b 0101 0101 0101 0101
    // ~b - 0b 0101 0101 1010 1010  AND   - NOT swaps 0 to 1, and 1 to 0
    //   -> 0b 0101 0101 0000 0000
    //      0x 5500

    // Left shift
    printf("c << 6 = %d\n", c << 6);
    // c - 0b 0000 0000 0000 0001 << 6    - Shift all bits to the left, fills with 0s
    //  -> 0b 0000 0000 0100 0000
    //     0x 0040

    // Right shift
    printf("a >> 4 = 0x%04x\n", a >> 4);
    // a - 0b 0101 0101 0101 0101 >> 4        - Shift all bits to the right, fills with 0s (usually)
    //  -> 0b 0000 0101 0101 0101
    //     0x 0555
}
