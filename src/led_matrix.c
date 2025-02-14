#include "led_matrix.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"

#define LED_PIN_1 2  // Primeiro LED da matriz
#define LED_PIN_2 3
#define LED_PIN_3 4
#define LED_PIN_4 5  // Ajuste conforme sua matriz
#define LED_PIN_5 6
#define LED_PIN_6 7

#define TOTAL_LEDS 6 // Se houver mais LEDs, aumente aqui

static const int led_pins[TOTAL_LEDS] = {LED_PIN_1, LED_PIN_2, LED_PIN_3, LED_PIN_4, LED_PIN_5, LED_PIN_6};

void led_matrix_init() {
    for (int i = 0; i < TOTAL_LEDS; i++) {
        gpio_init(led_pins[i]);
        gpio_set_dir(led_pins[i], GPIO_OUT);
        gpio_put(led_pins[i], 0); // Inicializa desligado
    }
}

void led_matrix_show_beat(int beat, int time_signature) {
    // Apaga todos os LEDs antes de acender o novo
    for (int i = 0; i < TOTAL_LEDS; i++) {
        gpio_put(led_pins[i], 0);
    }

    // Acende o LED correspondente à batida
    if (beat < time_signature && beat < TOTAL_LEDS) {
        gpio_put(led_pins[beat], 1);
    }
}