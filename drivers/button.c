#include <stdio.h>
#include <pico/stdlib.h>
//iniciar a gravação
#define BUTTON_A_PIN 5 
//Reproduz a gravação
#define BUTTON_B_PIN 6

void init_buttons(){
    gpio_init(BUTTON_A_PIN);
    gpio_set_dir(BUTTON_A_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_A_PIN);

    gpio_init(BUTTON_B_PIN);
    gpio_set_dir(BUTTON_B_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_B_PIN);
}
bool is_button_pressed(uint gpio) {
    if (gpio_get(gpio) == 0) {
        sleep_ms(50); // Simple debounce delay
        if (gpio_get(gpio) == 0) {
            return true;
        }
    }
    return false;
}