#include <stdio.h>
#include "include/buzzer.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "pico/stdlib.h"

#define BUZZER_A_PIN 21  // Pino do Buzzer A
#define BUZZER_B_PIN 10  // Pino do Buzzer B
#define FREQUENCY 2700   // Frequência do buzzer passivo
#define DUTY_CYCLE 50    // Percentual de ativação do PWM (0 a 100%)


//tive que criar a funcao pois o compilador nao estava encontrando
uint16_t pwm_get_wrap(uint slice_num) {
    return pwm_hw->slice[slice_num].top;
}

void buzzer_init() {
    // Configura GPIOs como PWM
    gpio_set_function(BUZZER_A_PIN, GPIO_FUNC_PWM);
    gpio_set_function(BUZZER_B_PIN, GPIO_FUNC_PWM);

    // Obtém o número do slice e canal PWM para cada buzzer
    uint slice_A = pwm_gpio_to_slice_num(BUZZER_A_PIN);
    uint slice_B = pwm_gpio_to_slice_num(BUZZER_B_PIN);
    uint channel_A = pwm_gpio_to_channel(BUZZER_A_PIN);
    uint channel_B = pwm_gpio_to_channel(BUZZER_B_PIN);

    // Calcula os valores corretos para a frequência de 2.7 kHz
    float clock_freq = clock_get_hz(clk_sys);
    float divider = 8.0;  // Pode ser ajustado para estabilidade
    uint16_t wrap_value = (clock_freq / divider) / FREQUENCY;

    // Configura o divisor de clock e o período do PWM
    pwm_set_clkdiv(slice_A, divider);
    pwm_set_clkdiv(slice_B, divider);
    pwm_set_wrap(slice_A, wrap_value);
    pwm_set_wrap(slice_B, wrap_value);

    // Ativa o PWM
    pwm_set_enabled(slice_A, true);
    pwm_set_enabled(slice_B, true);
}

void buzzerA_beep() {
    uint slice_A = pwm_gpio_to_slice_num(BUZZER_A_PIN);
    uint channel_A = pwm_gpio_to_channel(BUZZER_A_PIN);

    // Define o nível do duty cycle para gerar som
    pwm_set_chan_level(slice_A, channel_A, pwm_get_wrap(slice_A) * DUTY_CYCLE / 100);
    sleep_ms(100);
    pwm_set_chan_level(slice_A, channel_A, 0);  // Desliga o som
}

void buzzerB_beep() {
    uint slice_B = pwm_gpio_to_slice_num(BUZZER_B_PIN);
    uint channel_B = pwm_gpio_to_channel(BUZZER_B_PIN);

    // Ajustando para um tom mais grave
    uint16_t wrap_value = (clock_get_hz(clk_sys) / 8) / 1800; //Frequencia Hz
    pwm_set_wrap(slice_B, wrap_value);

    // Define o nível do duty cycle para gerar som
    pwm_set_chan_level(slice_B, channel_B, pwm_get_wrap(slice_B) * DUTY_CYCLE / 100);
    sleep_ms(100);
    pwm_set_chan_level(slice_B, channel_B, 0);  // Desliga o som
}