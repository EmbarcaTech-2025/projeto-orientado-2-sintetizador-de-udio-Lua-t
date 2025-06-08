#include "pico/stdlib.h"

void set_led_color(uint red_pin, uint green_pin, bool R, bool G) {
    gpio_put(red_pin, R);   // gravando
    gpio_put(green_pin, G); // reproduzindo
}
void pin_led(){
    const uint red_pin = 13;   // Pino para o LED vermelho
    const uint green_pin = 11; // Pino para o LED verde

    gpio_init(red_pin);
    gpio_init(green_pin);

    gpio_set_dir(red_pin, GPIO_OUT);
    gpio_set_dir(green_pin, GPIO_OUT);

    // Variáveis binárias para os estados dos LEDs - começa com todos apagados
    bool R = 0; // Vermelho
    bool G = 0; // Verde
    }
