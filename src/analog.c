#include "include/analog.h"
#include "hardware/adc.h"

#define POTENTIOMETER_PIN 26  // GPIO26 (ADC0)
#define MIN_BPM 30
#define MAX_BPM 240
#define THRESHOLD 10  // Sensibilidade do potenciômetro para mudanças
#define STEP_SIZE 1   // O BPM aumentará ou diminuirá de 1 em 1

static int last_adc_value = -1; // Última leitura bruta do ADC
static int current_bpm = 120;  // BPM inicial fixo

void analog_init() {
    adc_init();
    adc_gpio_init(POTENTIOMETER_PIN);
    adc_select_input(0); // Configura para ler o ADC0
}

int analog_read_bpm() {
    uint16_t raw_value = adc_read(); // Lê o valor do ADC (0 - 4095)
    
    // Se for a primeira leitura, define o valor inicial
    if (last_adc_value == -1) {
        last_adc_value = raw_value;
    }

    // Calcula a diferença entre a nova e a última leitura
    int delta = raw_value - last_adc_value;

    // Só ajusta o BPM se a mudança for maior que o THRESHOLD
    if (delta > THRESHOLD) {
        if (current_bpm < MAX_BPM) {
            current_bpm += STEP_SIZE; // Aumenta de 1 em 1
        }
    } else if (delta < -THRESHOLD) {
        if (current_bpm > MIN_BPM) {
            current_bpm -= STEP_SIZE; // Diminui de 1 em 1
        }
    }

    // Atualiza o último valor lido
    last_adc_value = raw_value;

    return current_bpm; // Retorna o BPM atualizado
}