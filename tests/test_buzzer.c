#include "../include/buzzer.h"
#include "pico/stdlib.h"

int main() {
    stdio_init_all();
    buzzer_init();

    while (1) {
        buzzerA_beep();
        sleep_ms(500); // Pausa de 500ms entre os beeps
        buzzerB_beep();
        sleep_ms(500);
    }
}