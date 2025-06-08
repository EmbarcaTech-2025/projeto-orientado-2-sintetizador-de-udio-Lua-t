#include <math.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/dma.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

#define MIC_CHANNEL 2
#define MIC_PIN (26 + MIC_CHANNEL)
#define SAMPLES_RATE 8000
#define SAMPLES_TIME 5
#define SAMPLES SAMPLES_RATE*SAMPLES_TIME  // 1 segundo a 8kHz
#define AUDIO_PIN 21

void adc_audio_init();
void pwm_audio_play(uint pin);
void adc_audio_record();
void pwm_audio_init(uint pin);
void display_init();