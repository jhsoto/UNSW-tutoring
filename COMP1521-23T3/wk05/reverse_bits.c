// Reverse the bits of a number using bit masks

#include <stdio.h>
#include <stdint.h>

int main() {
    uint16_t n = 0xFACE;
    uint16_t n_reverse = 0x0000;

    // TODO: Reverse n's bits
    printf("0x%X\n", n_reverse);
}


































/*
Which of the following correctly EXTRACT the i'th bit (from the right) of 'n'?
A)
uint16_t mask = 1;
uint16_t bit = (n & mask) << i;

B)
uint16_t mask = 1;
uint16_t bit = n | (mask << i);

C)
uint16_t bit = n & i;

D)
uint16_t mask = 1 << i;
uint16_t bit = n & mask;
*/