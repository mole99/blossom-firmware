#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <avr/io.h>
#include <avr/interrupt.h>

#include <leds.h>
#include <patterns.h>

enum {
  INACTIVE,
  ACTIVE
} typedef state_t;

extern volatile state_t current_state;

extern volatile uint8_t wdt_inactive_cnt;

void initWDT();

#endif
