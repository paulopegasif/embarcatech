#include "led_matrix.h"
#include "ws2812.pio.h"

#define NUM_LEDS 25
#define MATRIX_WIDTH 5
#define MATRIX_HEIGHT 5
#define WS2812_PIN 7

PIO pio;
uint sm;

void led_matrix_init() {
    uint offset = pio_add_program(pio0, &ws2812_program);
    ws2812_program_init(pio0, 0, offset, WS2812_PIN, 800000, false);
}

void update_led_matrix(uint8_t x, uint8_t y) {
    uint32_t color = (x + y) % 2 == 0 ? 0x00FF00 : 0xFF0000; // Alternar cores
    for (int i = 0; i < NUM_LEDS; i++) {
        uint led_x = i % MATRIX_WIDTH;
        uint led_y = i / MATRIX_WIDTH;
        uint32_t pixel = (led_x == x && led_y == y) ? color : 0x000000;
        pio_sm_put_blocking(pio0, 0, pixel);
    }
}