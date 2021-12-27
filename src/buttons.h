#ifndef BUTTONS_H
#define BUTTONS_H

#include <avr/io.h>
#include <avr/interrupt.h>

#include <watchdog.h>

enum {
  NOT_PRESSED = 0,
  DEADTIME,
  PRESSED
} typedef button_state_t;

struct {
  button_state_t state;
  uint16_t time_ms;
} typedef button_t;

struct {
  button_t button_0;
  button_t button_1;
  button_t button_2;
} typedef buttons_t;

extern buttons_t buttons;

void initADC();

#endif
