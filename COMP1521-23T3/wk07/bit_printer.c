// Print bits of integers (positive and negative) and floats
// Feel free to use this yourself!

#include <stdint.h>
#include <stdio.h>

// Strange and dirty way to keep bits the same while changing data type to a uint32_t
union bitunion {
    uint32_t bits;
    int i;
    float f;
};

void print_bits(uint32_t n);

int main() {
    union bitunion getbits;
    // Prints bits of an integer
    printf("Integer to print bits of: ");
    scanf("%d", &getbits.i);
    printf("%d: ", getbits.i);
    print_bits(getbits.bits);
    // Prints bits of a float
    printf("Float to print bits of: ");
    scanf("%f", &getbits.f);
    printf("%f: ", getbits.f);
    print_bits(getbits.bits);

    // Show off floating point imprecision
    float x = 0.1;
    float y = 0.2;
    printf("0.1 + 0.2 = %0.9f\n", x + y);
    // This prints '0.1 + 0.2 = 0.300000012'

    return 0;
}

void print_bits(uint32_t n) {
    // Print every bit of n, starting from MSB
    for (int i = 31; i >= 0; i--) {
        uint32_t bit = (n >> i) & 0x1;
        // 'bit' will either be 1 or 0, so '0' + bit = '0' or '1'
        putchar('0' + bit);
    }
    putchar('\n');
}