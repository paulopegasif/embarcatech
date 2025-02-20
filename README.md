# Metrônomo com Raspberry Pi Pico W

Este projeto é um **metrônomo digital** desenvolvido utilizando o **Raspberry Pi Pico W** com o **hardware da BitDogLabs**. O metrônomo utiliza um **display OLED** para mostrar o BPM atual, um **buzzer** para marcar o ritmo e uma **matriz de LEDs** para indicar os compassos em tempo real. Além disso, possui **botões** para ajuste interativo do BPM.

---

## Funcionalidades

- Exibe o BPM atual no display OLED.
- Emite sons rítmicos com o buzzer.
- Matriz de LEDs sincronizada com os compassos.
- Botões para aumentar e diminuir o BPM.
- Mensagem motivacional exibida no display.

---

## Hardware Utilizado

- **Raspberry Pi Pico W** 
- **Display OLED 128x64 (I2C)**
  - **SDA** no **GP14**
  - **SCL** no **GP15**
- **Matriz de LEDs** para indicação de compassos
- **Buzzer** para emitir o som rítmico
- **Botões** para controle do BPM
- **Hub USB-C** para alimentação e upload do código

---

## Configuração e Instalação

### Pré-requisitos

- **VSCode** com a extensão **Pi Pico** instalada
- **CMake** e **GNU Make** configurados
- **SDK do Raspberry Pi Pico** instalado

### Clonando o Repositório

```bash
git clone https://github.com/paulopegasif/embarcatech.git
cd metronome-new

## Configurando o Ambiente
	1.	Abra o projeto no VSCode.
	2.	Certifique-se de que a extensão Pi Pico está instalada e ativa.
	3.	Selecione o arquivo CMakeLists.txt.
	4.	Clique em “Build” na extensão Pi Pico.

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