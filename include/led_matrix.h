#ifndef LED_MATRIX_H
#define LED_MATRIX_H

#include <stdint.h>
#include <stdbool.h>

// Inicializa a matriz de LEDs
void led_matrix_init();

// Atualiza a exibição dos LEDs para indicar a batida atual
void led_matrix_show_beat(int beat, int time_signature);

//Mostra numero na matiz
void led_matrix_show_compass(int beat);

void led_matrix_test_pattern();

//void led_matrix_update_loop();

int get_led_index(int x, int y);



#endif