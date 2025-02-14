#include "analog.h"
#include "hardware/adc.h"

#define POTENTIOMETER_PIN 26  // GPIO26 (ADC0)
#define MIN_BPM 30
#define MAX_BPM 240

void analog_init() {
    adc_init();
    adc_gpio_init(POTENTIOMETER_PIN);
    adc_select_input(0); // Configura para ler o ADC0
}

int analog_read_bpm() {
    uint16_t raw_value = adc_read(); // Lê o valor do ADC (0 - 4095)
    
    // Converte para BPM dentro da faixa desejada
    int bpm = MIN_BPM + ((raw_value * (MAX_BPM - MIN_BPM)) / 4095);
    
    // Garante que o BPM fique dentro dos limites
    if (bpm < MIN_BPM) bpm = MIN_BPM;
    if (bpm > MAX_BPM) bpm = MAX_BPM;

    return bpm;
}