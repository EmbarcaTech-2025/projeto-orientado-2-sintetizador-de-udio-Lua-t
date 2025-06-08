#include <stdio.h>
#include "adc_audio.h"
#include "button.h"
#include "led_rgb.h"
#include "ssd1306.h"
ssd1306_t display;
int main(){
    stdio_init_all();
    init_buttons();
    pwm_audio_init(AUDIO_PIN);
    pin_led();
    adc_audio_init();
    display_init();
    while(true){
            absolute_time_t start = get_absolute_time();
            ssd1306_draw_string(&display, 0, 0, 1, "(A) Gravar");
            ssd1306_draw_string(&display, 0, 10,1 , "(B) Reproduzir");
            ssd1306_show(&display);
            sleep_ms(4000);
            ssd1306_clear(&display);
        if(gpio_get(BUTTON_A_PIN) == 0){
            gpio_put(green_pin, 0); 
            gpio_put(red_pin, 1); 
            adc_audio_record();
        }
        else if(gpio_get(BUTTON_B_PIN)==0){
            gpio_put(red_pin, 0);
            gpio_put(green_pin, 1);  
            pwm_audio_play(AUDIO_PIN); 

        }
        else {
            gpio_put(green_pin, 0); 
            gpio_put(red_pin, 0); 
        }
    }
    return 0;
}
