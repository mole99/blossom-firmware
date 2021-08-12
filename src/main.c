#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>

#include <leds.h>
#include <utils.h>
#include <patterns.h>
#include <sequences.h>
#include <watchdog.h>

/*

* Blossom Firmware *

General concept:

- INACTIVE 
	- Use WDT to wait for ~4s
  - Start ADC conversion
  - If value > threshold
  	- Go to ACTIVE
  
- ACTIVE
  - Use Timer 0 for multiplexing
  	- 54Hz refresh rate for the LEDs
  	- Start ADC conversion
	- Use Timer 1 for regular measurements
		- Intervall of 1 ms
		- Used for sleeping
		- Used for button deadtime
	- Upon ADC conversion complete
		- Set button states accordingly
		- Reset WDT counter
  - Use WDT to wait for ~30s
  	- Go to INACTIVE
  
*/

void displayPatternBlocking()
{
  // Go for two rounds
  for (int i=0; i < 12 * 2; i++)
  {
    activateLED(i%12);
    _delay_ms(20);
  }
  // Turn off
  activateLED(-1);
}

int main(void) 
{
	// Set everything as an input
	DDRB = 0x00;

	// Initialize all
	initADC();
	initTimer0();
	initTimer1();
  initWDT();
  
  // Disable analog comparator
  ACSR |= (1<<ACD);
	
	// Enable interrupts
  sei();
  
  pattern0_bootupPattern(1500, 500);

	while (1)
	{
		// When inactive, power down
		if (current_state == INACTIVE)
    {
			// Set everything as an input
			// and deactivate pullups
			DDRB = 0x00;
			PORTB = 0x00;
      
      // Disable ADC
      ADCSRA &= ~(1<<ADEN);

      set_sleep_mode(SLEEP_MODE_PWR_DOWN);
      sleep_bod_disable();
      sei();
      sleep_mode();

      // Enable ADC
      ADCSRA |= (1<<ADEN);
    }
    // When active, do stuff
    else
    {
      set_sleep_mode(SLEEP_MODE_IDLE);
      sei();
      sleep_mode();
      
      if (buttons.button_0.state == PRESSED)
      {
	    	pattern1_pulseSoft(3000, 1000);
      }
      else if (buttons.button_1.state == PRESSED)
      {
	    	pattern3_fireRingSoft(5000, 1000);
      }
      else if (buttons.button_2.state == PRESSED)
      {
	    	sequence0_heartBeatHard(2);
      }
      
      /*pattern4_starsHard(5000, 1000);
	    sleep_ms(2000);
      
	    pattern3_fireRingSoft(5000, 1000);
	    sleep_ms(2000);
	    pattern2_fireRingHard(5000, 1000);
	    sleep_ms(2000);
	    pattern0_pulseHard(3000, 1000);
	    sleep_ms(2000);
	    pattern1_pulseSoft(3000, 1000);
	    sleep_ms(2000);
	    sequence0_heartBeatHard(2);
	    sleep_ms(2000);
	    sequence1_heartBeatSoft(2);
      sleep_ms(2000);
	    pattern99_lightning(3000, 500);
	    
	    current_state = INACTIVE;

      //deactivateADCInterrupt(); // Necessary?
      activateLED(-1);*/
      
    }
	}

	return 0;  
}
