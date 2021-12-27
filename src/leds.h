#ifndef LEDS_H
#define LEDS_H

#include <avr/io.h>
#include <avr/interrupt.h>

#define NUM_LEDS 12
#define MAX_INTENSITY 15

extern uint8_t led_array[12];

void initTimer0();

void activateLED(uint8_t index);

#endif
