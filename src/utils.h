#ifndef UTILS_H
#define UTILS_H

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

#include <buttons.h>

extern uint8_t intensity_lut[16];

void initTimer1();

void sleep_ms(uint16_t time_ms);

#endif
