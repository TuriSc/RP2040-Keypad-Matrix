/*
* RP2040-Keypad-Matrix
* Keypad matrix polling library for Raspberry Pi Pico
*
* Author:Turi Scandurra
* Release date: 2023-02-13
*/

#include "keypad.h"

void keypad_init(KeypadMatrix* keypad_struct, uint8_t cols[KEYPAD_MATRIX_SIZE], uint8_t rows[KEYPAD_MATRIX_SIZE]){
    for (uint8_t i = 0; i < KEYPAD_MATRIX_SIZE; i++) {
        keypad_struct->_cols[i] = cols[i];
        keypad_struct->_rows[i] = rows[i];

        gpio_init(cols[i]);
        gpio_init(rows[i]);
        gpio_set_dir(cols[i], GPIO_IN);
        gpio_set_dir(rows[i], GPIO_OUT);
    }
}

bool * keypad_read(KeypadMatrix* keypad_struct){
    for (uint8_t row = 0; row < KEYPAD_MATRIX_SIZE; row++) {
        gpio_put(keypad_struct->_rows[row], 1);
        busy_wait_us(10000);
        for (int col = 0; col < KEYPAD_MATRIX_SIZE; col++) {
            keypad_struct->pressed[KEYPAD_MATRIX_SIZE * row + col] = gpio_get(keypad_struct->_cols[col]);
        }
        gpio_put(keypad_struct->_rows[row], 0);
    }
    return keypad_struct->pressed;
}