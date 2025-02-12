#ifndef ANALOG_H
#define ANALOG_H

#include "pico/stdlib.h"
#include "hardware/adc.h"

void analog_init();
uint16_t read_analog_x();
uint16_t read_analog_y();

#endif // ANALOG_H