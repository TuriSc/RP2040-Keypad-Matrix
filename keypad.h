/*
* RP2040-Keypad-Matrix
* Keypad matrix polling library for Raspberry Pi Pico
*
* Author:Turi Scandurra
* Release date: 2023-02-13
*/

#ifndef RP2040_KEYPAD_H
#define RP2040_KEYPAD_H

#include <pico/stdlib.h>

#define KEYPAD_MATRIX_SIZE 5

typedef struct {
    uint8_t _cols[KEYPAD_MATRIX_SIZE];
    uint8_t _rows[KEYPAD_MATRIX_SIZE];
    bool pressed [KEYPAD_MATRIX_SIZE * KEYPAD_MATRIX_SIZE];
} KeypadMatrix;

void keypad_init(KeypadMatrix* keypad_struct, uint8_t cols[], uint8_t rows[]);

bool * keypad_read(KeypadMatrix* keypad_struct);

#endif