#include <stdio.h>
#include "pico/stdlib.h"
#include "include/buttons.h"
#include "include/buzzer.h"
#include "include/display.h"
#include "include/led_matrix.h"

#define MIN_BPM 40
#define MAX_BPM 240
#define TIME_SIGNATURE 4

volatile int bpm = 120;
volatile int current_beat = 0;


void metronome_callback() {

    if (current_beat == 0) {
        buzzerA_beep();
    } else {
        buzzerB_beep();
    }
    led_matrix_show_compass(current_beat + 1);
    current_beat = (current_beat + 1) % TIME_SIGNATURE;
}



int main() {
    stdio_init_all();
    buttons_init();
    buzzer_init();
    display_init();
    led_matrix_init();

    sleep_ms(2000); // Debug

    // Chamando a barra de carregamento antes de iniciar
    led_matrix_test_pattern();
    display_loading_bar(&bpm);
    printf("Metrônomo iniciado!\n");


    while (1) {
        if (button_a_pressed() && bpm > MIN_BPM) {
            bpm--;
            printf("Botão A pressionado! BPM: %d\n", bpm);
            display_show_bpm(bpm);
            sleep_ms(200);
        }

        if (button_b_pressed() && bpm < MAX_BPM) {
            bpm++;
            printf("Botão B pressionado! BPM: %d\n", bpm);
            display_show_bpm(bpm);
            sleep_ms(200);
        }

        sleep_ms(60000 / bpm);
        metronome_callback();
    }

    return 0;
}