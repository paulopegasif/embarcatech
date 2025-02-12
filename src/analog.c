#include "analog.h"

#define PIN_JOYSTICK_X 26
#define PIN_JOYSTICK_Y 27

void analog_init() {
    adc_init();
    adc_gpio_init(PIN_JOYSTICK_X);
    adc_gpio_init(PIN_JOYSTICK_Y);
}

uint16_t read_analog_x() {
    adc_select_input(0);  // Canal 0 para X
    return adc_read();
}

uint16_t read_analog_y() {
    adc_select_input(1);  // Canal 1 para Y
    return adc_read();
}