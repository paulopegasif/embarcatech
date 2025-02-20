# Metrônomo com Raspberry Pi Pico W

Este projeto é um **metrônomo digital** desenvolvido utilizando o **Raspberry Pi Pico W** com o **hardware da BitDogLabs**. O metrônomo utiliza um **display OLED** para mostrar o BPM atual, um **buzzer** para marcar o ritmo e uma **matriz de LEDs** para indicar os compassos em tempo real. Além disso, possui **botões** para ajuste interativo do BPM.

---

## Funcionalidades

- Exibe o BPM atual no display OLED.
- Emite sons rítmicos com o buzzer.
- Matriz de LEDs sincronizada com os compassos.
- Botões para aumentar e diminuir o BPM.
- Mensagem do andamento atual (BPM) exibida no display.

---

## Hardware Utilizado

- **Raspberry Pi Pico W** 
- **Display OLED 128x64 (I2C)**
- **Matriz de LEDs** para indicação de compassos
- **Buzzer** para emitir o som rítmico
- **Botões** para controle do BPM
- **Hub USB-C** para alimentação e upload do código

---

## Instalação e Configuração

### Pré-requisitos

- **VSCode** com a extensão **Pi Pico** instalada
- **CMake** e **GNU Make** configurados
- **SDK do Raspberry Pi Pico** instalado
- Extensões para C e Raspiberry Pico no VSCode


### Funcionalidades dos Módulos

Display OLED (display.c e display.h)
	•	Inicializa o display via I2C.
	•	Exibe o BPM atual e mensagens no display OLED.

Buzzer (buzzer.c e buzzer.h)
	•	Emite pulsos rítmicos com base no BPM definido.

Botões (buttons.c e buttons.h)
	•	Aumenta e diminui o BPM de forma interativa.

Matriz de LEDs (led_matrix.c e led_matrix.h)
	•	Atualiza os LEDs conforme os compassos do metrônomo.
	•	Sincronização precisa com o buzzer para marcação visual do ritmo.

Hardware Init (hardware_init.c e hardware_init.h)
	•	Configuração inicial dos pinos do Raspberry Pi Pico W.


### Autor

Desenvolvido por Paulo Silva. Sinta-se à vontade para contribuir, sugerir melhorias ou relatar problemas!
Este metrônomo foi criado para fornecer uma experiência precisa e interativa para músicos e entusiastas de tecnologia. Mantenha o ritmo!
