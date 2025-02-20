#include <stdio.h>
#include "pico/stdlib.h"
#include "include/buttons.h"
#include "include/buzzer.h"
#include "include/display.h"
#include "include/led_matrix.h"

#define MIN_BPM 40
#define MAX_BPM 240
#define TIME_SIGNATURE 4

volatile int bpm = 60;
volatile int current_beat = 0;
uint64_t next_beat_time_us;

// Função para tocar o beep e mostrar o compasso
void play_beat() {
    if (current_beat == 0) {
        buzzerA_beep();  // Som forte no tempo 1
    } else {
        buzzerB_beep();  // Som fraco nos demais tempos
    }

    // Mostra o compasso na matriz LED
    led_matrix_show_compass(current_beat + 1);

    // Incrementa o compasso e reseta no final
    current_beat = (current_beat + 1) % TIME_SIGNATURE;
}

// Função para calcular o tempo do próximo beat com acumulação
void update_next_beat_time() {
    uint64_t interval_us = (60000000 / bpm); // Intervalo em microssegundos
    next_beat_time_us += interval_us;
}

int main() {
    stdio_init_all();
    buttons_init();
    buzzer_init();
    display_init();
    led_matrix_init();

    // Chamando a barra de carregamento antes de iniciar
    led_matrix_test_pattern();
    display_loading_bar(&bpm);

    printf("Metrônomo iniciado!\n");

    // Mostra o compasso no display
    display_show_time_signature(TIME_SIGNATURE); 

    // Inicializa o tempo do próximo beat com o tempo atual + intervalo
    next_beat_time_us = time_us_64() + (60000000 / bpm);

    while (1) {
        // Verifica se é hora de tocar o próximo beat
        if (time_us_64() >= next_beat_time_us) {
            play_beat();
            update_next_beat_time();  // Calcula o tempo do próximo beat
        }

        // Controle dos botões
        if (button_a_pressed() && bpm > MIN_BPM) {
            bpm--;
            printf("Botão A pressionado! BPM: %d\n", bpm);
            display_show_bpm(bpm);

            // Atualiza o tempo do próximo beat ao alterar o BPM
            next_beat_time_us = time_us_64() + (60000000 / bpm);
            sleep_ms(200);
        }

        if (button_b_pressed() && bpm < MAX_BPM) {
            bpm++;
            printf("Botão B pressionado! BPM: %d\n", bpm);
            display_show_bpm(bpm);

            // Atualiza o tempo do próximo beat ao alterar o BPM
            next_beat_time_us = time_us_64() + (60000000 / bpm);
            sleep_ms(200);
        }
    }

    return 0;
}