/**
 * @file keypad.c
 * @brief Keypad matrix polling library for Raspberry Pi Pico SDK
 *
 * @author Turi Scandurra
 * @version 1.2.0
 * @date 2023-10-27
 */

#include "keypad.h"

/**
 * @brief No-op function for callback
 *
 * @param key Key number
 */
void noop(uint8_t key){ ; }

/**
 * @brief Set the size of the keypad matrix
 *
 * @param _kp Pointer to the KeypadMatrix structure
 * @param cols_num Number of columns
 * @param rows_num Number of rows
 */
void keypad_set_size(KeypadMatrix* _kp, uint8_t cols_num, uint8_t rows_num){
    _kp->size = cols_num * rows_num;
    _kp->cols_num = cols_num;
    _kp->rows_num = rows_num;
}

/**
 * @brief Set the column and row GPIOs for the keypad matrix
 *
 * @param _kp Pointer to the KeypadMatrix structure
 * @param cols Array of column GPIOs
 * @param rows Array of row GPIOs
 */
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

/**
 * @brief Initialize the keypad matrix
 *
 * @param _kp Pointer to the KeypadMatrix structure
 * @param cols Array of column GPIOs
 * @param rows Array of row GPIOs
 * @param cols_num Number of columns
 * @param rows_num Number of rows
 */
void keypad_init(KeypadMatrix* _kp, const uint8_t *cols, const uint8_t *rows, uint8_t cols_num, uint8_t rows_num){
    // Set keypad size
    keypad_set_size(_kp, cols_num, rows_num);

    // Init GPIOs
    keypad_set_keys(_kp, cols, rows);

    // Initialize fallback callbacks
    _kp->on_press = noop;
    _kp->on_long_press = noop;
    _kp->on_release = noop;

    _kp->hold_threshold = HOLD_THRESHOLD_DEFAULT;
}

/**
 * @brief Set the callback function for key press event
 *
 * @param _kp Pointer to the KeypadMatrix structure
 * @param callback Callback function
 */
void keypad_on_press(KeypadMatrix* _kp, void (*callback)(uint8_t key)){
    _kp->on_press = callback;
}

/**
 * @brief Set the callback function for long press event
 *
 * @param _kp Pointer to the KeypadMatrix structure
 * @param callback Callback function
 */
void keypad_on_long_press(KeypadMatrix* _kp, void (*callback)(uint8_t key)){
    _kp->on_long_press = callback;
}

/**
 * @brief Set the callback function for key release event
 *
 * @param _kp Pointer to the KeypadMatrix structure
 * @param callback Callback function
 */
void keypad_on_release(KeypadMatrix* _kp, void (*callback)(uint8_t key)){
    _kp->on_release = callback;
}

/**
 * @brief Read the current state of the keypad matrix
 *
 * @param _kp Pointer to the KeypadMatrix structure
 * @return Pointer to the array of key press states
 */
bool * keypad_read(KeypadMatrix* _kp){
    uint64_t now = time_us_64();
    for (uint8_t row = 0; row < _kp->rows_num; row++) {
        gpio_put(_kp->_rows[row], 1);
        busy_wait_us(10000);
        for (int col = 0; col < _kp->cols_num; col++) {
            uint8_t k = (_kp->cols_num * row) + col;
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
                    if (duration > (_kp->hold_threshold * 1000) && !_kp->long_pressed[k]){
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

/**
 * @brief Set the hold threshold for long press detection
 *
 * @param _kp Pointer to the KeypadMatrix structure
 * @param threshold_ms Hold threshold in milliseconds
 */
void keypad_set_hold_threshold(KeypadMatrix* _kp, uint16_t threshold_ms){
    _kp->hold_threshold = threshold_ms;
}

