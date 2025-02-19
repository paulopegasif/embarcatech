#ifndef BUZZER_H
#define BUZZER_H

#include <stdint.h>

// Inicializa os buzzers
void buzzer_init();

// Emite um beep curto no Buzzer A
void buzzerA_beep();

// Emite um beep curto no Buzzer B
void buzzerB_beep();

// Define o tempo entre os beeps baseado no BPM
void buzzer_set_tempo(uint16_t bpm);

#endif