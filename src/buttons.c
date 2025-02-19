#include "include/buttons.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"

#define BUTTON_A_PIN 5  // Defina os pinos corretos
#define BUTTON_B_PIN 6  // Botão B para Play/Pause
#define DEBOUNCE_TIME 200  // Tempo de debounce em ms

void buttons_init() {
    gpio_init(BUTTON_A_PIN);
    gpio_set_dir(BUTTON_A_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_A_PIN);  // Habilita pull-up interno

    gpio_init(BUTTON_B_PIN);
    gpio_set_dir(BUTTON_B_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_B_PIN);
}

bool button_a_pressed() {
    return !gpio_get(BUTTON_A_PIN); // Retorna `true` se o botão for pressionado
}

bool button_b_pressed() {
    static uint32_t last_press_time = 0;
    bool current_state = !gpio_get(BUTTON_B_PIN); // Botão ativo em LOW
    uint32_t now = to_ms_since_boot(get_absolute_time());

    if (current_state && (now - last_press_time > DEBOUNCE_TIME)) {
        last_press_time = now;
        return true;
    }

    return false;
}