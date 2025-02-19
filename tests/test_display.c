#include "../include/display.h"
#include "pico/stdlib.h"

int main() {
    stdio_init_all();
    display_init();

    while (1) {
        display_show_bpm(120);
        sleep_ms(2000);
        display_show_time_signature(4);
        sleep_ms(2000);
    }
}