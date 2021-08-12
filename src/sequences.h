#ifndef SEQUENCES_H
#define SEQUENCES_H

#include <avr/io.h>
#include <patterns.h>

extern uint8_t led_array[12];

void sequence0_heartBeatHard(uint8_t repetitions);
void sequence1_heartBeatSoft(uint8_t repetitions);

#endif
