#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/dma.h"
#include "hardware/pwm.h"
#include "adc_audio.h"
#include "hardware/i2c.h"
#include "ssd1306.h"
#define I2C_PORT i2c1

const uint I2C_SDA = 14;
const uint I2C_SCL = 15;
// Buffers de áudio (uint8_t para PWM de 8 bits)
uint8_t audio_buffer[SAMPLES];
ssd1306_t display;

void display_init(){
    i2c_init(I2C_PORT, 400000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    display.external_vcc=false;
    ssd1306_init(&display, 128, 64, 0x3C, I2C_PORT);
    ssd1306_clear(&display);
}

void adc_audio_init() {
    adc_gpio_init(MIC_PIN);
    adc_init();
    adc_select_input(MIC_CHANNEL);
}

void adc_audio_record() {
    absolute_time_t start = get_absolute_time();
    // ssd1306_draw_string(&display, 0, 0, 1, "(A) Gravar");
    // ssd1306_draw_string(&display, 0, 10,1 , "(B) Reproduzir");
    // ssd1306_show(&display);
    // ssd1306_clear(&display);
    for (int i = 0; i < SAMPLES; i++) {
        audio_buffer[i] = adc_read() >> 4;

        if(i % 4096 == 0 && i > 0) {
            ssd1306_clear(&display);
            for(int x=i-128; x<i && x < SAMPLES; x++){
                int h=audio_buffer[x]/4;
                if(h>=32){
                    ssd1306_draw_line(&display,x-(i-128),32,x-(i-128),h);
                }
                else{
                   ssd1306_draw_line(&display,x-(i-128),h,x-(i-128),32);
                }
            }
            ssd1306_show(&display);
        }

        // Taxa de amostragem de 8kHz = 125us por amostra
        sleep_until(delayed_by_us(start, i * 125));
    }
    ssd1306_clear(&display);
    ssd1306_show(&display);
}

void pwm_audio_init(uint pin) {
    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(pin);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 1.0f);
    pwm_config_set_wrap(&config, 255); // 8-bit áudio
    pwm_init(slice, &config, true);
    pwm_set_gpio_level(pin, 0);
}

void pwm_audio_play(uint pin) {
    uint slice = pwm_gpio_to_slice_num(pin);
    absolute_time_t start = get_absolute_time();

    for (int i = 0; i < SAMPLES; i++) {
        pwm_set_gpio_level(pin, audio_buffer[i]);
        // Taxa de amostragem de 8kHz = 125us por amostra
        sleep_until(delayed_by_us(start, i * 125));
    }

    pwm_set_gpio_level(pin, 0); // Silêncio no final
}
//draw_string

