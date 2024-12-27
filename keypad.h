/**
 * @file keypad.h
 * @brief Keypad matrix polling library for Raspberry Pi Pico SDK
 *
 * @author Turi Scandurra
 * @version 1.2.0
 * @date 2023-10-27
 */

#ifndef RP2040_KEYPAD_H
#define RP2040_KEYPAD_H

#include <pico/stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @def SIDE_MAX_SIZE
 * @brief Maximum size of a side of the keypad matrix (8x8 by default)
 */
#define SIDE_MAX_SIZE   8

/**
 * @def HOLD_THRESHOLD_DEFAULT
 * @brief Default hold threshold for long press detection (1500ms)
 */
#define HOLD_THRESHOLD_DEFAULT  1500

/**
 * @struct KeypadMatrix
 * @brief Structure representing a keypad matrix
 */
typedef struct {
    /**
     * @brief Column GPIOs
     */
    uint8_t _cols[SIDE_MAX_SIZE];

    /**
     * @brief Row GPIOs
     */
    uint8_t _rows[SIDE_MAX_SIZE];

    /**
     * @brief Current key press state
     */
    bool pressed[SIDE_MAX_SIZE * SIDE_MAX_SIZE];

    /**
     * @brief Previous key press state
     */
    bool previous_pressed[SIDE_MAX_SIZE * SIDE_MAX_SIZE];

    /**
     * @brief Long press state
     */
    bool long_pressed[SIDE_MAX_SIZE * SIDE_MAX_SIZE];

    /**
     * @brief Key press times
     */
    uint64_t press_times[SIDE_MAX_SIZE * SIDE_MAX_SIZE];

    /**
     * @brief Number of columns
     */
    uint8_t cols_num;

    /**
     * @brief Number of rows
     */
    uint8_t rows_num;

    /**
     * @brief Total number of keys
     */
    uint16_t size;

    /**
     * @brief Hold threshold for long press detection
     */
    uint16_t hold_threshold;

    /**
     * @brief Callback function for key press event
     */
    void (*on_press)(uint8_t key);

    /**
     * @brief Callback function for long press event
     */
    void (*on_long_press)(uint8_t key);

    /**
     * @brief Callback function for key release event
     */
    void (*on_release)(uint8_t key);
} KeypadMatrix;

/**
 * @brief Set the size of the keypad matrix
 *
 * @param keypad_struct Pointer to the KeypadMatrix structure
 * @param cols_num Number of columns
 * @param rows_num Number of rows
 */
void keypad_set_size(KeypadMatrix* keypad_struct, uint8_t cols_num, uint8_t rows_num);

/**
 * @brief Set the column and row GPIOs for the keypad matrix
 *
 * @param keypad_struct Pointer to the KeypadMatrix structure
 * @param cols Array of column GPIOs
 * @param rows Array of row GPIOs
 */
void keypad_set_keys(KeypadMatrix* keypad_struct, const uint8_t *cols, const uint8_t *rows);

/**
 * @brief Initialize the keypad matrix
 *
 * @param keypad_struct Pointer to the KeypadMatrix structure
 * @param cols Array of column GPIOs
 * @param rows Array of row GPIOs
 * @param cols_num Number of columns
 * @param rows_num Number of rows
 */
void keypad_init(KeypadMatrix* keypad_struct, const uint8_t *cols, const uint8_t *rows, uint8_t cols_num, uint8_t rows_num);

/**
 * @brief Read the current state of the keypad matrix
 *
 * @param keypad_struct Pointer to the KeypadMatrix structure
 * @return Pointer to the array of key press states
 */
bool * keypad_read(KeypadMatrix* keypad_struct);

/**
 * @brief Set the callback function for key press event
 *
 * @param _kp Pointer to the KeypadMatrix structure
 * @param callback Callback function
 */
void keypad_on_press(KeypadMatrix* _kp, void (*callback)(uint8_t key));

/**
 * @brief Set the callback function for long press event
 *
 * @param _kp Pointer to the KeypadMatrix structure
 * @param callback Callback function
 */
void keypad_on_long_press(KeypadMatrix* _kp, void (*callback)(uint8_t key));

/**
 * @brief Set the callback function for key release event
 *
 * @param _kp Pointer to the KeypadMatrix structure
 * @param callback Callback function
 */
void keypad_on_release(KeypadMatrix* _kp, void (*callback)(uint8_t key));

/**
 * @brief Set the hold threshold for long press detection
 *
 * @param _kp Pointer to the KeypadMatrix structure
 * @param threshold_ms Hold threshold in milliseconds
 */
void keypad_set_hold_threshold(KeypadMatrix* _kp, uint16_t threshold_ms);

#ifdef __cplusplus
}
#endif

#endif

