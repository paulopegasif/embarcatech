#include "../include/led_matrix.h"
#include "pico/stdlib.h"

int main() {
    stdio_init_all();
    led_matrix_init();

    int beat = 0;
    int time_signature = 4; // Testando um compasso 4/4

    while (1) {
        led_matrix_show_beat(beat, time_signature);
        sleep_ms(500); // Intervalo de tempo para simular o BPM
        beat = (beat + 1) % time_signature;
    }
}