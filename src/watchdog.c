#include <watchdog.h>

volatile state_t current_state = ACTIVE;
volatile uint8_t wdt_inactive_cnt = 0;

void initWDT()
{
  // Activate interrupt and enable watchdog, 
  // set prescaler to 512K cycles ~4.0s
  WDTCR = (1<<WDIE) | (1<<WDP3);
}

ISR(WDT_vect)
{
  if (current_state == INACTIVE)
  {
    // Enable ADC
    ADCSRA |= (1<<ADEN);
  
    // Start conversion
    ADCSRA |= (1<<ADSC);
    
    // Wait for conversion to finish
    while (ADCSRA & (1<<ADSC));

    // Read the result (high byte)
    uint8_t result = ADCH;
    
    // If greater than some threshold
    // a button must be pressed
    if (result > 42)
    {
      wdt_inactive_cnt = 0;
      current_state = ACTIVE;
      pattern0_bootupPattern(1500, 500);
    }
    else
    {
      // Disable ADC
      ADCSRA &= ~(1<<ADEN);
    }
  }
  else
  {
    // Get back to inactive state after 8 * 4 = 32s
    if (wdt_inactive_cnt++ >= 8)
    {
      current_state = INACTIVE;
      activateLED(-1);
    }
  }
}
