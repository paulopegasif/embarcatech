#ifndef ANALOG_H
#define ANALOG_H

#include <stdint.h>
#include <stdbool.h>

// Inicializa o potenciômetro e o botão embutido
void analog_init();

// Lê o BPM ajustado pelo potenciômetro
int analog_read_bpm();

// Verifica se o botão do potenciômetro foi pressionado
//bool analog_button_pressed();

#endif