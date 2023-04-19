/*
* RP2040-Keypad-Matrix
* Keypad matrix polling library for Raspberry Pi Pico
*
* Author:Turi Scandurra
* 
* Version history:
* 2023-04-19 - v1.1.0 - Detect long presses; better example
* 2023-02-13 - v1.0.0 - First release
*/

#include "keypad.h"

void noop(uint8_t key){ ; }

void keypad_set_size(KeypadMatrix* _kp, uint8_t cols_num, uint8_t rows_num){
    _kp->size = cols_num * rows_num;
    _kp->cols_num = cols_num;
    _kp->rows_num = rows_num;
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

void keypad_init(KeypadMatrix* _kp, const uint8_t *cols, const uint8_t *rows, uint8_t cols_num, uint8_t rows_num){
    // Set keypad size
    keypad_set_size(_kp, cols_num, rows_num);

    // Init GPIOs
    keypad_set_keys(_kp, cols, rows);

    // Initialize fallback callbacks
    _kp->on_press = noop;
    _kp->on_long_press = noop;
    _kp->on_release = noop;
}

void keypad_on_press(KeypadMatrix* _kp, void (*callback)(uint8_t key)){
    _kp->on_press = callback;
}

void keypad_on_long_press(KeypadMatrix* _kp, void (*callback)(uint8_t key)){
    _kp->on_long_press = callback;
}

void keypad_on_release(KeypadMatrix* _kp, void (*callback)(uint8_t key)){
    _kp->on_release = callback;
}

bool * keypad_read(KeypadMatrix* _kp){
    uint64_t now = time_us_64();
    for (uint8_t row = 0; row < _kp->rows_num; row++) {
        gpio_put(_kp->_rows[row], 1);
        busy_wait_us(10000);
        for (int col = 0; col < _kp->cols_num; col++) {
            uint8_t k = (_kp->rows_num * row) + col;
            _kp->pressed[k] = gpio_get(_kp->_cols[col]);

            if(_kp->pressed[k] != _kp->previous_pressed[k]){
                if(_kp->pressed[k]) {
                    _kp->on_press(k);
                    _kp->press_times[k] = now;
                } else {
                    _kp->on_release(k);
                    _kp->long_pressed[k] = false;
                }
                _kp->previous_pressed[k] = _kp->pressed[k];
            } else {
                if(_kp->pressed[k]){
                    uint64_t duration = now - _kp->press_times[k];
                    if (duration > (HOLD_THRESHOLD * 1000) && !_kp->long_pressed[k]){
                        _kp->on_long_press(k);
                        _kp->long_pressed[k] = true;
                    }
                }
            }
        }
        gpio_put(_kp->_rows[row], 0);
    }
    return _kp->pressed;
}