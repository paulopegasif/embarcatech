#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

// Inicializa o display OLED
void display_init();

// Exibe o BPM na tela
void display_show_bpm(int bpm);

// Exibe o compasso (4/4, 3/4, etc.)
void display_show_time_signature(int signature);

#endif