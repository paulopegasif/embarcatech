#ifndef ANALOG_H
#define ANALOG_H

#include <stdint.h>

// Inicializa a leitura analógica
void analog_init();

// Lê o potenciômetro e retorna um BPM entre 30 e 240
int analog_read_bpm();

#endif