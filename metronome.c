#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

// Defs para o Display OLED
#define I2C_PORT i2c0
#define I2C_SDA 14
#define I2C_SCL 15
#define OLED_ADDR 0x3c

// Def dos botoes e Buzzer
#define BUTTON_INC 5 //Botao para aumentar o BPM
#define BUTTON_DEC 6 //Botao para diminuir o BPM
#define BUZZER_PIN 20

int bpm = 120; //BPM inicial

//Funcao para inicializar o display
void oled_init() {
    uint8_t cmds[] = {
        0xAE, 0x20, 0x00, 0xB0, 0xC8, 0x00, 0x10, 0x40,
        0x81, 0xFF, 0xA1, 0xA6, 0xA8, 0x3F, 0xA4, 0xD3,
        0x00, 0xD5, 0xF0, 0xD9, 0x22, 0xDA, 0x12, 0xDB,
        0x20, 0x8D, 0x14, 0xAF
    };
    for (int i = 0; i < sizeof(cmds); i++) {
        uint8_t buf[2] = {0x00, cmds[i]};
        i2c_write_blocking(I2C_PORT, OLED_ADDR, buf, 2, false);
    }

    printf("OLED inicializado!\n");
}

//Funcao para limpar o display
void oled_clear() {
    for (uint8_t page = 0; page < 8; page++) {
        uint8_t buf[] = {0x00, (uint8_t)(0xB0 + page), 0x00, 0x10};
        i2c_write_blocking(I2C_PORT, OLED_ADDR, buf, 4, false);
        uint8_t clear[129] = {0x40};
        memset(clear + 1, 0x00, 128);
        i2c_write_blocking(I2C_PORT, OLED_ADDR, clear, 129, false);
    }
    printf("OLED limpo!\n");
}

// Funcao para exibir o BPM no display
void oled_display_bpm(int bpm) {
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "BPM: %d", bpm);
    // Aqui voce pode adicionar o codigo para desenhar os caracteres no display
    // Dependendo da biblioteca ou metodo que preferir
    printf("BPM exibido: %d\n", bpm);
}

// Funcao para emitir o som do metrônomo
void beep() {
    gpio_put(BUZZER_PIN, 1);
    sleep_ms(50);
    gpio_put(BUZZER_PIN, 0);
    printf("Beepando!\n");
}

int main(){
    stdio_init_all();
    printf("Metrônomo iniciado!\n");

    //Inicializando o I2C para o display
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    oled_init();
    oled_clear();
    oled_display_bpm(bpm);

    //Config dos botoes e buzzer
    //Botao INC
    gpio_init(BUTTON_INC);
    gpio_set_dir(BUTTON_INC, GPIO_IN);
    gpio_pull_up(BUTTON_INC);

    //Bota DEC
    gpio_init(BUTTON_DEC);
    gpio_set_dir(BUTTON_DEC, GPIO_IN);
    gpio_pull_up(BUTTON_DEC);

    //Buzzer
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);

    printf("Metronomo iniciado!\n");


    while(true){
        //Verifica se o botao aumentar BPM foi pressionado
        if (!gpio_get(BUTTON_INC)){
            bpm +=1; //Incrementa +1 bpm
            oled_display_bpm(bpm);
            sleep_ms(200); 
        }

        //Verifica se o botao diminuir BPM foi pressionado
        if(!gpio_get(BUTTON_DEC)){
            bpm -=1; //Decrementa -1 bpm
            oled_display_bpm(bpm);
            sleep_ms(200);
        }

        //Emite o som de acordo com o BPM;
        beep();
        sleep_ms(6000 / bpm);

    }

    return 0;

}