// Program to demonstrate a few bitwise operations!
// Comment/uncomment each printf to see what happens.

#include <stdio.h>
#include <stdint.h>     // This adds all the fixed-sized integer defintions

int main() {
    // Always use UNSIGNED integers when working with bitwise operations
    // Signed integers have strange behaviour when being right shifted (more on why next time!)
    uint16_t a = 0x5555;
    uint16_t b = 0xAA55;
    uint16_t c = 0x0001;

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
}
