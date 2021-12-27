#include <utils.h>

uint8_t intensity_lut[16] = 
{
  0,
  1,
  2,
  3,
  4,
  5,
  8,
  10,
  14,
  17,
  21,
  26,
  31,
  36,
  42,
  48,
};

volatile uint16_t timer1_sleep_ms = 0;

void sleep_ms(uint16_t time_ms)
{
  timer1_sleep_ms = time_ms;
  
  while (timer1_sleep_ms > 0)
  {
    set_sleep_mode(SLEEP_MODE_IDLE);
    sei();
    sleep_mode();
  }
}

void initTimer1()
{
  // Enable overflow interrupt
  TIMSK |= (1<<TOIE1);
  
  // Reset prescaler
  GTCCR = (1<<PSR1);
  
  // Start at zero
  TCNT1 = 0;
  
  // Set prescaler to 32, start timer
  TCCR1 = (1<<CS12) | (1<<CS11);
}

// ~1 ms = 1000 Hz
ISR(TIMER1_OVF_vect)
{
  if (timer1_sleep_ms > 0)
  {
      timer1_sleep_ms--;
  }
  
  // Increase the time for the buttons if pressed
  if (buttons.button_0.state != NOT_PRESSED)
  {
    buttons.button_0.time_ms++;
  }
  else if (buttons.button_1.state != NOT_PRESSED)
  {
    buttons.button_1.time_ms++;
  }
  else if (buttons.button_2.state != NOT_PRESSED)
  {
    buttons.button_2.time_ms++;
  }
}
