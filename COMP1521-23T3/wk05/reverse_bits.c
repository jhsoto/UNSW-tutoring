// Reverse the bits of a number using bit masks

// SUMMARY:
//       mask - put a 1 where you want something (setting/extracting) to happen
//            - you can have a mask that covers multiple bits e.g. mask = 0x3 << 1 = 0b 0000 0110
//    setting - n | mask -> sets masked bits to 1 without affecting other bits
// extracting - n & mask -> extracts only masked bits, other bits set to 0

#include <stdio.h>
#include <stdint.h>

int main() {
    uint16_t n = 0xFACE;
    // 0xFACE = 0b 1111 1010 1100 1110
    uint16_t n_reverse = 0x0000;
    // reverse: 0b 0111 0011 0101 1111 = 0x735F

    for (int i = 0; i < 16; i++) {
        // Adding a 'u' after a number makes it unsigned - remember always unsigned with bitwise!
        uint16_t extract_mask = 1u << i;
        // Say i = 6
        // 1u = 0b 0000 0000 0000 0001
        //      left shift 6
        //   -> 0b 0000 0000 0100 0000
        //                    ^ bit to extract
        uint16_t set_mask = 1u << (15 - i);
        // 1u = 0b 0000 0000 0000 0001
        //      right shift 15 - 6 = 9
        //   -> 0b 0000 0010 0000 0000
        //                ^ bit to set

        // n & extract_mask:
        //   0b 1111 1010 1100 1110
        // & 0b 0000 0000 0100 0000
        // = 0b 0000 0000 0100 0000
        //
        // The extracted bit was set to 1, so we should set the corresponding bit in n_reverse
        // If it was 0, there would be no need to set anything, n_reverse has all zeroes initially
        if (n & extract_mask) {
            // n_reverse | set_mask:
            //   0b 0111 0000 0000 0000   <- let's assume n_reverse has been set correctly so far
            // | 0b 0000 0010 0000 0000
            // = 0b 0111 0010 0000 0000
            //
            // We have set the bit to 1
            n_reverse |= set_mask;
        }
    }

    printf("0x%X\n", n_reverse);
}