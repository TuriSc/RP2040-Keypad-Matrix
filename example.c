#include <stdio.h>
#include <pico/stdlib.h>
#include "keypad.h"

uint8_t cols[] = {4, 3, 2, 1, 0}; // Keypad matrix column GPIOs
uint8_t rows[] = {9, 8, 7, 6, 5}; // Keypad matrix row GPIOs

KeypadMatrix keypad_1;

static bool keypad_task() {
    keypad_read(&keypad_1);

    /* Alternatively, the output of keypad_read() can
    be stored as a pointer to the array containing
    the state of each key:
    bool *pressed = keypad_read(&keypad_1);
    */

    // After calling keypad_read(), the current state of
    // the keypad can be compared with values from the previous scan:
    for(uint8_t i=0; i<keypad_1.size; i++) {
        if(keypad_1.pressed[i] != keypad_1.previous_pressed[i]){ // the pressed state has changed
            if(keypad_1.pressed[i]){
                printf("Key %d pressed\n",i);
                keypad_1.previous_pressed[i] = true;
            } else { // the key is not pressed, but it was before
                keypad_1.previous_pressed[i] = false;
                printf("Key %d released\n",i);
            }
        }
    }
}

int main() {
    stdio_init_all();

    // Declare the number of columns and rows
    keypad_set_size(&keypad_1, 5, 5);

    // Apply the configuration defined earlier 
    keypad_set_keys(&keypad_1, cols, rows);

    while (true) {
        keypad_task();
        sleep_ms(50);
    }
}