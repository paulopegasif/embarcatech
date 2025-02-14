#include "display.h"
#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include "ssd1306.h" // Biblioteca do display OLED

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
    ssd1306_clear(&oled_display);
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