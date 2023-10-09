// Program to control a printer.
// The printer has various settings stored as individual bits in a control variable.

#include <stdio.h>
#include <stdint.h>

// The bits of this variable control the printer
uint8_t printerControl = 0; // 0b 0000 0000
// printerControl = 0 0 0 0 0 0 0 0
//                          ^ ^ ^ ^
//                          | | | |
//                          | | | L [NO_INK]
//                          | | L [COLOUR]
//                          | L [SELECT_PRINT]
//                          L [SELECT_SCAN]

// Whether the printer is out of ink  -> 0 means OK, 1 means out of ink
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
    // TODO
}

// Replace the ink the printer
void replaceInk() {
    // TODO
}

// Select the colour and scan modes (assuming no other mode has been set)
void selectColourScan() {
    // TODO
}

// Toggle between printing and scanning mode
void togglePrintScan() {
    // TODO
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