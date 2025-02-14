#include <stdio.h>
#include "pico/stdlib.h"
#include "buzzer.h"
#include "buttons.h"
#include "analog.h"
#include "display.h"
#include "led_matrix.h"

// Configurações iniciais
#define DEFAULT_BPM 120  // BPM inicial
#define MIN_BPM 30       // BPM mínimo
#define MAX_BPM 240      // BPM máximo
#define TIME_SIGNATURE 4 // Compasso 4/4 (pode ser alterado depois)

static int bpm = DEFAULT_BPM; // BPM atual
static int beat_counter = 0;  // Contador de batidas

void setup() {
    stdio_init_all();
    buzzer_init();
    buttons_init();
    analog_init();
    display_init();
    led_matrix_init();
}

void loop() {
    // Lê o BPM do potenciômetro
    int new_bpm = analog_read_bpm();
    if (new_bpm != bpm) {
        bpm = new_bpm;
    }
    
    // Verifica se o botão TAP foi pressionado
    if (button_a_pressed()) {
        int tap_bpm = button_a_tap_tempo();
        if (tap_bpm != -1) {
            bpm = tap_bpm;
        }
    }
    
    // Atualiza o display com o BPM atual
    display_show_bpm(bpm);
    
    // Calcula o intervalo entre batidas
    int beat_delay = 60000 / bpm; // Tempo entre beeps em milissegundos
    
    // Gera os beeps de acordo com o compasso
    if (beat_counter == 0) {
        buzzerA_beep();  // Buzzer A no primeiro tempo (tempo forte)
    } else {
        buzzerB_beep();  // Buzzer B nos tempos fracos
    }
    
    // Atualiza a matriz de LEDs para indicar a batida atual
    led_matrix_show_beat(beat_counter, TIME_SIGNATURE);

    // Avança o contador de batidas no compasso
    beat_counter = (beat_counter + 1) % TIME_SIGNATURE;

    // Espera até a próxima batida
    sleep_ms(beat_delay);
}

int main() {
    setup();
    while (1) {
        loop();
    }
}