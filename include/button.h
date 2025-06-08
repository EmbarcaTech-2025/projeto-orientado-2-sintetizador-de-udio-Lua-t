#include <stdio.h>
#include <pico/stdlib.h>
#define BUTTON_A_PIN 5 
#define BUTTON_B_PIN 6
void init_buttons();
bool is_button_pressed(uint gpio);