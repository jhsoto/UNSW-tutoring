// Extract the middle 6 bits of a 32 bit number

#include <stdint.h>
#include <stdio.h>

int main(void) {
    uint32_t n = 0xDEADBEEF;    // = 0b 1101 1110 1010 1101 1011 1110 1110 1111
                                //      Want to extract ^-----^
    uint32_t result = 0;        //                -> 0b 101 101 = 0x2D

    // Make a mask that is 6 bits long
    uint32_t mask = 0x3F;   // = 0b111111
    // Initially, this mask is sitting at the right side (LSB)
    //    n: 0b 1101 1110 1010 1101 1011 1110 1110 1111
    // mask: 0b 0000 0000 0000 0000 0000 0000 0011 1111

    // Move the mask into position
    // We want to move past 13 bits to reach the middle
    mask = mask << 13;
    // After the shift
    //    n: 0b 1101 1110 1010 1101 1011 1110 1110 1111
    // mask: 0b 0000 0000 0000 0111 1110 0000 0000 0000

    // Extract using the mask!
    result = n & mask;
    //      n: 0b 1101 1110 1010 1101 1011 1110 1110 1111
    //   mask: 0b 0000 0000 0000 0111 1110 0000 0000 0000 &
    // result: 0b 0000 0000 0000 0101 1010 0000 0000 0000

    // Almost done, but we want our result in the bottom 6 bits
    // We want to move the result past 13 bits
    result = result >> 13;
    // Finally,
    // result: 0b 0000 0000 0000 0000 0000 0000 0010 1101

    printf("Middle 6 bits: 0x%02X\n", result);

    return 0;
}