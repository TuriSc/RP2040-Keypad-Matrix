#include <stdio.h>
#include <pico/stdlib.h>
#include "keypad.h"

uint8_t cols[] = {4, 3, 2, 1, 0}; // Keypad matrix column GPIOs
uint8_t rows[] = {9, 8, 7, 6, 5}; // Keypad matrix row GPIOs

#define keys_num (sizeof(cols) * sizeof(rows))

KeypadMatrix keypad;
bool previous_pressed_keys[keys_num];

static bool keypad_task() {
    // The output of keypad_read() is an array containing
    // the state of each key.
    bool *pressed = keypad_read(&keypad);

    for(uint8_t i=0; i<keys_num; i++) {
        if(pressed[i] != previous_pressed_keys[i]){ // if the pressed state has changed
            if(pressed[i]){
                printf("Key %d pressed\n",i);
                previous_pressed_keys[i] = true;
            } else { // the key is not pressed, but it was before
                previous_pressed_keys[i] = false;
                printf("Key %d released\n",i);
            }
        }
    }
}

int main() {
    stdio_init_all();

    while (true) {
        keypad_task();
        sleep_ms(50);
    }
}