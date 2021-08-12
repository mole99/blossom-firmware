#ifndef PATTERNS_H
#define PATTERNS_H

#include <avr/io.h>
#include <utils.h>

extern uint8_t led_array[12];

void pattern0_bootupPattern(uint16_t duration_ms, uint16_t period_ms);
void pattern0_pulseHard(uint16_t duration_ms, uint16_t period_ms);
void pattern1_pulseSoft(uint16_t duration_ms, uint16_t period_ms);
void pattern2_fireRingHard(uint16_t duration_ms, uint16_t period_ms);
void pattern3_fireRingSoft(uint16_t duration_ms, uint16_t period_ms);
void pattern4_starsHard(uint16_t duration_ms, uint16_t period_ms);

void pattern99_lightning(uint16_t duration_ms, uint16_t period_ms);

#endif
