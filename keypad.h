/*
* RP2040-Keypad-Matrix
* Keypad matrix polling library for Raspberry Pi Pico
*
* Author:Turi Scandurra
* 
* Version history:
* 2023-10-27 - v1.2.0 - Hold threshold can now be customized at runtime
* 2023-04-19 - v1.1.0 - Detect long presses; better example
* 2023-02-13 - v1.0.0 - First release
*/

#ifndef RP2040_KEYPAD_H
#define RP2040_KEYPAD_H

#include <pico/stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

// By default the library supports keypads up to 8x8 keys in size.
// Adjust the following value in case your matrix is larger.
#define SIDE_MAX_SIZE   8

#define HOLD_THRESHOLD_DEFAULT  1500 // How many milliseconds to hold a key to trigger a 'long press'

typedef struct {
    uint8_t _cols[SIDE_MAX_SIZE];
    uint8_t _rows[SIDE_MAX_SIZE];
    bool pressed[SIDE_MAX_SIZE * SIDE_MAX_SIZE];
    bool previous_pressed[SIDE_MAX_SIZE * SIDE_MAX_SIZE];
    bool long_pressed[SIDE_MAX_SIZE * SIDE_MAX_SIZE];
    uint64_t press_times[SIDE_MAX_SIZE * SIDE_MAX_SIZE];
    uint8_t cols_num;
    uint8_t rows_num;
    uint16_t size;
    uint16_t hold_threshold;
    void (*on_press)(uint8_t key);
    void (*on_long_press)(uint8_t key);
    void (*on_release)(uint8_t key);
} KeypadMatrix;

void keypad_set_size(KeypadMatrix* keypad_struct, uint8_t cols_num, uint8_t rows_num);

void keypad_set_keys(KeypadMatrix* keypad_struct, const uint8_t *cols, const uint8_t *rows);

void keypad_init(KeypadMatrix* keypad_struct, const uint8_t *cols, const uint8_t *rows, uint8_t cols_num, uint8_t rows_num);

bool * keypad_read(KeypadMatrix* keypad_struct);

void keypad_on_press(KeypadMatrix* _kp, void (*callback)(uint8_t key));

void keypad_on_long_press(KeypadMatrix* _kp, void (*callback)(uint8_t key));

void keypad_on_release(KeypadMatrix* _kp, void (*callback)(uint8_t key));

void keypad_set_hold_threshold(KeypadMatrix* _kp, uint16_t threshold_ms);

#ifdef __cplusplus
}
#endif

#endif
