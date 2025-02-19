#ifndef BUTTONS_H
#define BUTTONS_H

#include <stdbool.h>
#include <stdint.h>

// Inicializa os botões
void buttons_init();

// Retorna `true` se o Botão A foi pressionado
bool button_a_pressed();

// Retorna `true` se o Botão B foi pressionado
bool button_b_pressed();

// Calcula BPM baseado no tempo entre toques no Botão A
int button_a_tap_tempo();

#endif