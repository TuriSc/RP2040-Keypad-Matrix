/**
 * @file example/example.c
 * @brief Example usage of the keypad matrix library
 *
 * @author Turi Scandurra
 * @version 1.2.0
 * @date 2023-10-27
 */

#include <stdio.h>
#include <pico/stdlib.h>
#include "keypad.h" // Import the library. https://github.com/TuriSc/RP2040-Keypad-Matrix

/**
 * @brief Define the keypad matrix column GPIOs
 */
const uint8_t cols[] = {4, 5, 6, 7};

/**
 * @brief Define the keypad matrix row GPIOs
 */
const uint8_t rows[] = {0, 1, 2, 3};

/**
 * @brief Create the keypad matrix structure
 */
KeypadMatrix keypad;

/**
 * @brief Callback function for key press event
 *
 * @param key Key number
 */
void key_pressed(uint8_t key){
    printf("Key %d pressed\n", key);
}

/**
 * @brief Callback function for key release event
 *
 * @param key Key number
 */
void key_released(uint8_t key){
    printf("Key %d released\n", key);
}

/**
 * @brief Callback function for long press event
 *
 * @param key Key number
 */
void key_long_pressed(uint8_t key){
    printf("Key %d long pressed\n", key);
}

/**
 * @brief Main function
 *
 * @return 0 on success
 */
int main() {
    stdio_init_all();

    // Apply the keypad configuration defined earlier 
    // and declare the number of columns and rows
    keypad_init(&keypad, cols, rows, 4, 4);

    // Assign the callbacks for each event
    keypad_on_press(&keypad, key_pressed);
    keypad_on_release(&keypad, key_released);
    keypad_on_long_press(&keypad, key_long_pressed);

    // Adjust the hold threshold to two seconds. Default is 1500ms
    keypad_set_hold_threshold(&keypad, 2000);

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

