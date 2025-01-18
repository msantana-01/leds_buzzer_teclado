# Controle de LEDs e Buzzer no Raspberry Pi Pico

Este projeto permite controlar três LEDs e um buzzer no **Raspberry Pi Pico** utilizando a linguagem C e a biblioteca `pico/stdlib.h`. O controle dos componentes é feito por meio de comandos no terminal serial.

## Componentes Utilizados

- **Raspberry Pi Pico**
- **3 LEDs** (verde, azul e vermelho)
- **1 Buzzer**

## Funcionalidades

O código permite controlar os seguintes componentes:

- **LED Verde (pino 11)**
- **LED Azul (pino 12)**
- **LED Vermelho (pino 13)**
- **Buzzer (pino 21)**

### Comandos no Terminal

Após a inicialização do código, o controle é feito através de comandos digitados no terminal serial conectado ao Raspberry Pi Pico. Os comandos são:

- **1**: Alterna o LED verde.
- **2**: Alterna o LED azul.
- **3**: Alterna o LED vermelho.
- **4**: Alterna o buzzer (emite som intermitente).
- **5**: Desliga todos os LEDs e o buzzer.
