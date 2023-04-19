#include <stdio.h>
#include <pico/stdlib.h>
#include "keypad.h" // Import the library. https://github.com/TuriSc/RP2040-Keypad-Matrix

// Define the keypad matrix column GPIOs
const uint8_t cols[] = {4, 5, 6, 7};
// Define the keypad matrix row GPIOs
const uint8_t rows[] = {0, 1, 2, 3};

// Create the keypad
KeypadMatrix keypad;

// Define the callbacks for each event
void key_pressed(uint8_t key){
    printf("Key %d pressed\n", key);
}

void key_released(uint8_t key){
    printf("Key %d released\n", key);
}

void key_long_pressed(uint8_t key){
    printf("Key %d long pressed\n", key);
}

int main() {
    stdio_init_all();

    // Apply the keypad configuration defined earlier 
    // and declare the number of columns and rows
    keypad_init(&keypad, cols, rows, 4, 4);

    // Assign the callbacks for each event
    keypad_on_press(&keypad, key_pressed);
    keypad_on_release(&keypad, key_released);
    keypad_on_long_press(&keypad, key_long_pressed);


    while (true) {
        // Poll the keypad
        keypad_read(&keypad);
        /* Alternatively, the output of keypad_read() can
        be stored as a pointer to the array containing
        the state of each key:
        bool *pressed = keypad_read(&keypad);
        */
        sleep_ms(5);
    }
}