#ifndef LED_MATRIX_H
#define LED_MATRIX_H

#include <stdint.h>

// Inicializa a matriz de LEDs
void led_matrix_init();

// Atualiza a exibição dos LEDs para indicar a batida atual
void led_matrix_show_beat(int beat, int time_signature);

#endif