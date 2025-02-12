#include <stdio.h>
#include "pico/stdlib.h"
#include "analog.h"
#include "led_matrix.h"

int main() {
    stdio_init_all();
    analog_init();
    led_matrix_init();

    while (1) {
        uint16_t x = read_analog_x();
        uint16_t y = read_analog_y();

        // Normalizar valores (de 0 a 4 para uma matriz 5x5)
        uint8_t pos_x = x * 5 / 4096;
        uint8_t pos_y = y * 5 / 4096;

        update_led_matrix(pos_x, pos_y);
        sleep_ms(100);
    }

    return 0;
}