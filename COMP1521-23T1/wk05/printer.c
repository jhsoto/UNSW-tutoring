// Program to control a printer.
// The printer has various settings stored as individual bits in a control variable.

// More complex bitwise operations:
// 
// clearing - n & ~mask -> sets all masked bits to 0 (clears) without affecting other bits
// toggling - n ^ mask -> toggles all masked bits i.e. 1s becomes 0s and 0s become 1s

#include <stdio.h>
#include <stdint.h>

// The bits of this variable control the printer
// The printer starts with no ink
uint8_t printerControl = 0x01; // 0b 0000 0001
// printerControl = 0 0 0 0 0 0 0 0
//                          ^ ^ ^ ^
//                          | | | |
//                          | | | L [NO_INK]
//                          | | L [COLOUR]
//                          | L [SELECT_PRINT]
//                          L [SELECT_SCAN]

// Whether the printer is out of ink -> 0 means OK, 1 means out of ink
#define NO_INK (0x1)       // 0b 0000 0001
// Whether to print/scan in colour -> 0 means Black & White, 1 means Colour
#define COLOUR (0x2)       // 0b 0000 0010
// Select print mode
#define SELECT_PRINT (0x4) // 0b 0000 0100
// Select scan mode
#define SELECT_SCAN (0x8)  // 0b 0000 1000

////////////////////////////////////////////////////////////
// Here are the printer functionalities to implement:
//
// Print whether the printer is out of ink or not
void printInkLevel();
// Replace the ink the printer
void replaceInk();
// Select the colour and scan modes (assuming no other mode has been set)
void selectColourScan();
// Toggle between printing and scanning mode
void togglePrintScan();

////////////////////////////////////////////////////////////
// Already implemented:
// Print the current mode the printer is set to
void printMode();


int main() {
    // Should be out of ink to start
    printInkLevel();

    // After replacing, there should be ink available
    replaceInk();
    printInkLevel();

    // Set the mode and print it
    selectColourScan();
    printMode();

    // Toggle from scan to print mode
    togglePrintScan();
    printMode();

    // Toggle back from print to scan mode
    togglePrintScan();
    printMode();
}

// Print whether the printer is out of ink or not
void printInkLevel() {
    // Test the NO_INK bit using the provided mask
    if (printerControl & NO_INK) {
        printf("Out of ink!\n");
    } else {
        printf("Ink levels OK.\n");
    }
}

// Replace the ink the printer
void replaceInk() {
    // Set the NO_INK bit to 0 to indicate there is ink left
    printerControl &= ~NO_INK;
    // Say are in colour print mode with no ink:
    // printer_control = 0b 0000 0111
    //         ~NO_INK = 0b 1111 1110 &
    //                 = 0b 0000 0110
    //
    // We clear the NO_INK bit without affecting other bits
}

// Select the colour and scan modes (assuming no other mode has been set)
void selectColourScan() {
    // Set the colour and select_scan bits (see reverse_bits for a more detailed breakdown)
    printerControl |= COLOUR;
    printerControl |= SELECT_SCAN;
}

// Toggle between printing and scanning mode
void togglePrintScan() {
    // Toggle both the scan and printing mode to swap between the two
    printerControl ^= SELECT_SCAN;
    // Say are in colour print mode with no ink:
    // printer_control = 0b 0000 0111
    //     SELECT_SCAN = 0b 0000 1000 ^
    //                 = 0b 0000 1111
    //
    // We toggled the SELECT_SCAN bit without affecting other bits
    printerControl ^= SELECT_PRINT;
    // printer_control = 0b 0000 0111
    //    SELECT_PRINT = 0b 0000 0100 ^
    //                 = 0b 0000 1011
    //
    // We toggled the SELECT_PRINT bit without affecting other bits
}

// Print the current mode the printer is set to
void printMode() {
    printf("Current mode: ");

    // Test the COLOUR bit
    if (printerControl & COLOUR) {
        printf("Colour");
    } else {
        printf("Black & White");
    }

    // Test the SELECT_PRINT bit
    if (printerControl & SELECT_PRINT) {
        printf(" Print");
    }

    // Test the SELECT_SCAN bit
    if (printerControl & SELECT_SCAN) {
        printf(" Scan");
    }

    printf("\n");
}




/*
Side note:
We could've used a few integer variables to store the printer settings, but this is inefficient.
Each setting is only every ON/OFF, we only need a single bit for this, but an integer takes up 32bits!
*/