#include <stdio.h>
#include "include/display.h"
#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include "include/ssd1306.h" // Biblioteca do display OLED

#define I2C_PORT i2c1
#define SDA_PIN 14
#define SCL_PIN 15
#define OLED_ADDR 0x3C

static ssd1306_t oled_display;


void display_init() {
    i2c_init(I2C_PORT, 400 * 1000); // Inicializa I2C com 400kHz
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    ssd1306_init(&oled_display, 128, 64, OLED_ADDR, I2C_PORT);

    // Reset do display para garantir que não haja ruído
    ssd1306_poweroff(&oled_display);
    sleep_ms(50);  // Aguarda o desligamento completo
    ssd1306_poweron(&oled_display);
    sleep_ms(50);  // Aguarda a religação

    // Limpeza dupla para garantir a tela preta
    ssd1306_clear(&oled_display);
    ssd1306_show(&oled_display);
    sleep_ms(50);  // Sincronização do hardware
    ssd1306_clear(&oled_display);
    ssd1306_show(&oled_display);

}

void display_show_bpm(int bpm) {
    char bpm_text[20];
    sprintf(bpm_text, "BPM: %d", bpm);

    ssd1306_clear(&oled_display);
    ssd1306_draw_string(&oled_display, 10, 20, 2, bpm_text);
    ssd1306_show(&oled_display);
}

void display_show_time_signature(int signature) {
    char sig_text[10];
    sprintf(sig_text, "%d/%d", signature, 4);

    ssd1306_draw_string(&oled_display, 10, 40, 2, sig_text);
    ssd1306_show(&oled_display);
}

void display_loading_bar(int *bpm) {
    // Desliga o display para apagar qualquer resíduo de pixels
    //ssd1306_poweroff(&oled_display);
    //sleep_ms(100);  // Aguarda um momento para garantir o desligamento completo

    // Liga o display novamente
    //ssd1306_poweron(&oled_display);
    //ssd1306_clear(&oled_display);  // Garante que o buffer esteja limpo
    //ssd1306_show(&oled_display);   // Exibe a tela limpa

    // Mensagem de carregamento
    ssd1306_draw_string(&oled_display, 10, 20, 1, "Carregando...");
    ssd1306_show(&oled_display);

    // Animação da barra de carregamento
    for (int i = 0; i <= 100; i += 10) {
        ssd1306_draw_line(&oled_display, 10, 40, 10 + i, 40);  // Linha cresce na horizontal
        ssd1306_show(&oled_display);
        sleep_ms(100);
    }

    // Exibe o BPM atual após o carregamento
    display_show_bpm(*bpm);
}