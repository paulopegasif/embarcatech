#include "buttons.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"

#define BUTTON_A_PIN 5  // Defina os pinos corretos
#define BUTTON_B_PIN 6

#define TAP_MAX_INTERVAL 2000  // Tempo máximo entre TAPs em ms (2s)
#define TAP_HISTORY_SIZE 4     // Quantos TAPs armazenamos para calcular BPM

static uint32_t tap_times[TAP_HISTORY_SIZE] = {0};
static int tap_index = 0;

void buttons_init() {
    gpio_init(BUTTON_A_PIN);
    gpio_set_dir(BUTTON_A_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_A_PIN);  // Puxar para evitar ruído

    gpio_init(BUTTON_B_PIN);
    gpio_set_dir(BUTTON_B_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_B_PIN);
}

bool button_a_pressed() {
    return !gpio_get(BUTTON_A_PIN); // Retorna verdadeiro se o botão for pressionado
}

bool button_b_pressed() {
    return !gpio_get(BUTTON_B_PIN); // Retorna verdadeiro se o botão for pressionado
}

int button_a_tap_tempo() {
    uint32_t now = to_ms_since_boot(get_absolute_time());

    // Calcula o tempo entre TAPs
    if (tap_index > 0) {
        uint32_t delta = now - tap_times[tap_index - 1];

        // Se o tempo entre TAPs for muito grande, resetamos o histórico
        if (delta > TAP_MAX_INTERVAL) {
            tap_index = 0;
        }
    }

    // Armazena o tempo atual
    tap_times[tap_index] = now;
    tap_index = (tap_index + 1) % TAP_HISTORY_SIZE;

    // Se ainda não temos toques suficientes, retorna o BPM atual
    if (tap_index < 2) {
        return -1; // Ainda não é possível calcular um BPM
    }

    // Calcula a média dos tempos entre TAPs
    uint32_t total_time = 0;
    for (int i = 1; i < tap_index; i++) {
        total_time += tap_times[i] - tap_times[i - 1];
    }

    uint32_t avg_time = total_time / (tap_index - 1); // Média dos intervalos

    // Calcula o BPM com base no tempo médio entre os TAPs
    int bpm = 60000 / avg_time;

    // Garante que o BPM esteja na faixa permitida
    if (bpm < 30) bpm = 30;
    if (bpm > 240) bpm = 240;

    return bpm;
}