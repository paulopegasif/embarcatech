#include "buzzer.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"

#define BUZZER_A_PIN 21  // Pino do Buzzer A
#define BUZZER_B_PIN 10  // Pino do Buzzer B

static uint16_t tempo_delay = 500; // Valor inicial baseado em ~120 BPM

void buzzer_init() {
    gpio_init(BUZZER_A_PIN);
    gpio_set_dir(BUZZER_A_PIN, GPIO_OUT);
    gpio_put(BUZZER_A_PIN, 0); // Mantém desligado

    gpio_init(BUZZER_B_PIN);
    gpio_set_dir(BUZZER_B_PIN, GPIO_OUT);
    gpio_put(BUZZER_B_PIN, 0); // Mantém desligado
}

void buzzerA_beep() {
    gpio_put(BUZZER_A_PIN, 1);  // Liga o buzzer A
    sleep_ms(50);               // Duração do beep (~50ms)
    gpio_put(BUZZER_A_PIN, 0);  // Desliga o buzzer A
}

void buzzerB_beep() {
    gpio_put(BUZZER_B_PIN, 1);  // Liga o buzzer B
    sleep_ms(50);               // Duração do beep (~50ms)
    gpio_put(BUZZER_B_PIN, 0);  // Desliga o buzzer B
}

void buzzer_set_tempo(uint16_t bpm) {
    if (bpm < 30) bpm = 30;   // Limite mínimo de BPM
    if (bpm > 240) bpm = 240; // Limite máximo de BPM

    // Calcula o tempo entre beeps: (60s / BPM) * 1000 para converter para ms
    tempo_delay = (60000 / bpm);
}