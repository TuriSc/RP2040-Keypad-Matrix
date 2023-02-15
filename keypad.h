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

// By default the library supports keypads up to 8x8 keys in size.
// Adjust the following value in case your matrix is larger.
#define SIDE_MAX_SIZE 8

typedef struct {
    uint8_t _cols[SIDE_MAX_SIZE];
    uint8_t _rows[SIDE_MAX_SIZE];
    bool pressed[SIDE_MAX_SIZE * SIDE_MAX_SIZE];
    bool previous_pressed[SIDE_MAX_SIZE * SIDE_MAX_SIZE];
    uint8_t cols_num;
    uint8_t rows_num;
    uint16_t size;
} KeypadMatrix;

void keypad_set_size(KeypadMatrix* keypad_struct, uint8_t cols, uint8_t rows);

void keypad_set_keys(KeypadMatrix* keypad_struct, uint8_t *cols, uint8_t *rows);

bool * keypad_read(KeypadMatrix* keypad_struct);

#endif