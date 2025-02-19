#include <stdio.h>
#include "include/led_matrix.h"
#include "hardware/gpio.h"
#include "hardware/pio.h"
#include "generated/ws2812.pio.h"
#include "pico/stdlib.h"

#define NUM_PIXELS 25
#define IS_RGBW false
#define LED_PIN 7
#define MATRIX_WIDTH 5
#define MATRIX_HEIGHT 5

static PIO pio = pio0;
static uint sm; // Máquina de estado para controle dos LEDs

// Função para converter coordenadas (x, y) para o índice correto na matriz WS2812
int get_led_index(int x, int y) {
    if (y % 2 == 1) {  // Se for uma linha IMPAR, a numeração é normal
        return y * MATRIX_WIDTH + x;
    } else {  // Se for uma linha PAR, a numeração é invertida
        return y * MATRIX_WIDTH + (MATRIX_WIDTH - 1 - x);
    }
}

// Envia um pixel de cor para o LED
static inline void put_pixel(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio, sm, pixel_grb << 8u);
    sleep_us(50);
}

// Converte valores RGB para o formato WS2812
static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return ((uint32_t)(r) << 8) | ((uint32_t)(g) << 16) | (uint32_t)(b);
}

// Apaga toda a matriz
void led_matrix_clear() {
    for (int i = 0; i < NUM_PIXELS; i++) {
        put_pixel(urgb_u32(0, 0, 0));
    }
}

// Inicializa a Matriz de LEDs WS2812
void led_matrix_init() {
    uint offset = pio_add_program(pio, &ws2812_program);
    sm = pio_claim_unused_sm(pio, true);
    ws2812_program_init(pio, sm, offset, LED_PIN, 800000, IS_RGBW);
    
    // Teste inicial: apaga os LEDs e pisca em branco
    led_matrix_clear();
    for (int i = 0; i < NUM_PIXELS; i++) {
        put_pixel(urgb_u32(50, 50, 50));  // Branco fraco
    }
    sleep_ms(500);
    led_matrix_clear();
}

// Exibe o compasso na matriz de LEDs
// Exibe o compasso na matriz de LEDs
void led_matrix_show_compass(int beat) {
    uint32_t led_colors[NUM_PIXELS] = {0}; // Array para armazenar as cores

    // Coluna 0 sempre acesa em branco
    for (int row = 0; row < MATRIX_HEIGHT; row++) {
        int index = get_led_index(0, row);
        led_colors[index] = urgb_u32(50, 50, 50);  // Branco fraco
    }

    // Acende as colunas conforme o tempo do compasso
    if (beat >= 1 && beat <= 4) {
        for (int row = 0; row < MATRIX_HEIGHT; row++) {
            int index = get_led_index(beat, row);

            // Se for o tempo forte (tempo 1), acende vermelho
            if (beat == 1) {
                led_colors[index] = urgb_u32(255, 0, 0); // Vermelho para tempo forte
            } else {
                led_colors[index] = urgb_u32(0, 255, 0); // Verde para outros tempos
            }
        }
    }

    // Envia todas as cores da matriz para os LEDs
    for (int i = 0; i < NUM_PIXELS; i++) {
        put_pixel(led_colors[i]);
    }
}

// Testa a matriz de LEDs acendendo um por um
void led_matrix_test_pattern() {
    printf("Testando mapeamento de LEDs...\n");

    uint32_t led_colors[NUM_PIXELS] = {0}; // Array para armazenar as cores

    for (int y = 0; y < MATRIX_HEIGHT; y++) {
        for (int x = 0; x < MATRIX_WIDTH; x++) {
            int index = get_led_index(x, y); // Obtém o índice correto do LED
            
            printf("Acendendo LED[%d,%d] -> Índice: %d\n", x, y, index);
            
            led_colors[index] = urgb_u32(0, 0, 255); // Define a cor AZUL no array
            
            // Envia todas as cores da matriz para os LEDs
            for (int i = 0; i < NUM_PIXELS; i++) {
                put_pixel(led_colors[i]);
            }
            
            sleep_ms(200);
        }
    }
}