#include "../include/buttons.h"
#include <stdio.h>
#include "pico/stdlib.h"

int main() {
    stdio_init_all();
    buttons_init();

    while (1) {
        if (button_a_pressed()) {
            printf("Botão A pressionado!\n");
            int bpm = button_a_tap_tempo();
            if (bpm != -1) {
                printf("BPM ajustado para: %d\n", bpm);
            }
            sleep_ms(200); // Evita leitura múltipla devido ao bounce
        }

        if (button_b_pressed()) {
            printf("Botão B pressionado!\n");
            sleep_ms(200);
        }
    }
}