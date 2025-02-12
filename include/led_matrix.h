#ifndef LED_MATRIX_H
#define LED_MATRIX_H

#include "pico/stdlib.h"
#include "hardware/pio.h"

void led_matrix_init();
void update_led_matrix(uint8_t x, uint8_t y);

#endif // LED_MATRIX_H