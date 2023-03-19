/*
* RP2040-Keypad-Matrix
* Keypad matrix polling library for Raspberry Pi Pico
*
* Author:Turi Scandurra
* Release date: 2023-02-13
*/

#include "keypad.h"

void keypad_set_size(KeypadMatrix* _kp, uint8_t cols, uint8_t rows){
    _kp->size = cols * rows;
    _kp->cols_num = cols;
    _kp->rows_num = rows;
}

void keypad_set_keys(KeypadMatrix* _kp, const uint8_t *cols, const uint8_t *rows){
    for (uint8_t i = 0; i < _kp->cols_num; i++) {
        _kp->_cols[i] = cols[i];
        gpio_init(cols[i]);
        gpio_set_dir(cols[i], GPIO_IN);
    }
    for (uint8_t i = 0; i < _kp->rows_num; i++) {
        _kp->_rows[i] = rows[i];
        gpio_init(rows[i]);
        gpio_set_dir(rows[i], GPIO_OUT);
    }
}

bool * keypad_read(KeypadMatrix* _kp){
    for (uint8_t row = 0; row < _kp->rows_num; row++) {
        gpio_put(_kp->_rows[row], 1);
        busy_wait_us(10000);
        for (int col = 0; col < _kp->cols_num; col++) {
            _kp->pressed[_kp->rows_num * row + col] = gpio_get(_kp->_cols[col]);
        }
        gpio_put(_kp->_rows[row], 0);
    }
    return _kp->pressed;
}