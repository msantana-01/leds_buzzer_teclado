#include "pico/stdlib.h"
#include <stdio.h>
#include <stdbool.h>

#define LED_VERDE 11
#define LED_AZUL 12
#define LED_VERMELHO 13
#define BUZZER 21

bool estado_led_verde = false;
bool estado_led_azul = false;
bool estado_led_vermelho = false;
bool estado_buzzer = false;

void ligar_led(int led, const char* cor) {
    gpio_put(LED_VERDE, 0);
    gpio_put(LED_AZUL, 0);
    gpio_put(LED_VERMELHO, 0);
    
    gpio_put(led, 1);
    printf("%s ligado\n", cor); // Exibe a mensagem no terminal
}

void desligar_led(int led, const char* cor) {
    gpio_put(led, 0);
    printf("%s desligado\n", cor); // Exibe a mensagem no terminal
}

void alternar_led(int led, bool* estado, const char* cor) {
    if (*estado) {
        desligar_led(led, cor);
    } else {
        ligar_led(led, cor);
    }
    *estado = !(*estado); // Inverte o estado do LED
}

void alternar_buzzer() {
    if (estado_buzzer) {
        gpio_put(BUZZER, 0); // Desliga o buzzer
        printf("Buzzer desligado\n");
    } else {
        // Desliga todos os LEDs antes de ligar o buzzer
        desligar_led(LED_VERDE, "LED verde");
        desligar_led(LED_AZUL, "LED azul");
        desligar_led(LED_VERMELHO, "LED vermelho");

        for (int i = 0; i < 1000; i++) { 
            gpio_put(BUZZER, 1);  // Liga o buzzer
            sleep_us(500);  // Aguarda 500 microssegundos
            gpio_put(BUZZER, 0);  // Desliga o buzzer
            sleep_us(500);  // Aguarda 500 microssegundos
        }
    }
    estado_buzzer = !estado_buzzer; // Inverte o estado do buzzer
}

void desligar_tudo() {
    desligar_led(LED_VERDE, "LED verde");
    desligar_led(LED_AZUL, "LED azul");
    desligar_led(LED_VERMELHO, "LED vermelho");
    gpio_put(BUZZER, 0); // Desliga o buzzer
    printf("Todos os componentes desligados\n");

    estado_led_verde = false;
    estado_led_azul = false;
    estado_led_vermelho = false;
    estado_buzzer = false;
}

int main() {
    // Inicializa a interface serial
    stdio_init_all();

    // Configura os pinos
    gpio_init(LED_VERDE);
    gpio_init(LED_AZUL);
    gpio_init(LED_VERMELHO);
    gpio_init(BUZZER);

    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_set_dir(LED_AZUL, GPIO_OUT);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_set_dir(BUZZER, GPIO_OUT);

    // Aguarda um caractere do teclado
    char input;
    while (true) {
        // Lê o input do terminal serial
        if (stdio_usb_connected()) {
            input = getchar();  // Leitura do teclado

            if (input != EOF) {
                // Verifica o que foi digitado e realiza a ação correspondente
                switch (input) {
                    case '1':  // Alternar LED verde
                        alternar_led(LED_VERDE, &estado_led_verde, "LED verde");
                        break;
                    case '2':  // Alternar LED azul
                        alternar_led(LED_AZUL, &estado_led_azul, "LED azul");
                        break;
                    case '3':  // Alternar LED vermelho
                        alternar_led(LED_VERMELHO, &estado_led_vermelho, "LED vermelho");
                        break;
                    case '4':  // Alternar buzzer
                        alternar_buzzer();
                        break;
                    case '5':  // Desligar todos os componentes
                        desligar_tudo();
                        break;
                    default:
                        break;
                }
            }
        }

        // Atraso de 50ms para evitar múltiplas leituras consecutivas sem querer
        sleep_ms(50);
    }

    return 0;
}
