#include <leds.h>

// PB0 - PB3 LEDs
#define LED0 PB0
#define LED1 PB1
#define LED2 PB2
#define LED3 PB3

uint8_t led_array[12] = {0};

void initTimer0()
{
  // Deactivate compare match, normal mode
  TCCR0A = 0x00;
  TCCR0B = 0x00;
  
  // Enable overflow interrupt
  TIMSK |= (1<<TOIE0);
  
  // Start at zero
  TCNT0 = 0;
  
  // Set no prescaler, start the timer
  TCCR0B = (0b01<<0);
}

void activateLED(uint8_t index)
{
  PORTB = 0x00;
  DDRB = 0x00;
  
  switch (index>>1)
  {
    case 0:
      // D1-D2
      DDRB |= ((1<<LED0) | (1<<LED1));
      if (index & 0x1 ) { PORTB |= (1<<LED0); PORTB &= ~(1<<LED1); }
      else { PORTB |= (1<<LED1); PORTB &= ~(1<<LED0); }
      break;
    case 1:
      // D3-D4
      DDRB |= ((1<<LED1) | (1<<LED2));
      if (index & 0x1 ) { PORTB |= (1<<LED1); PORTB &= ~(1<<LED2); }
      else { PORTB |= (1<<LED2); PORTB &= ~(1<<LED1); }
      break;
    case 2:
      // D5-D6
      DDRB |= ((1<<LED2) | (1<<LED3));
      if (index & 0x1 ) { PORTB |= (1<<LED2); PORTB &= ~(1<<LED3); }
      else { PORTB |= (1<<LED3); PORTB &= ~(1<<LED2); }
      break;
    case 3:
      // D7-D8
      DDRB |= ((1<<LED0) | (1<<LED2));
      if (index & 0x1 ) { PORTB |= (1<<LED0); PORTB &= ~(1<<LED2); }
      else { PORTB |= (1<<LED2); PORTB &= ~(1<<LED0); }
      break;
    case 4:
      // D9-D10
      DDRB |= ((1<<LED1) | (1<<LED3));
      if (index & 0x1 ) { PORTB |= (1<<LED1); PORTB &= ~(1<<LED3); }
      else { PORTB |= (1<<LED3); PORTB &= ~(1<<LED1); }
      break;
    case 5:
      // D11-D12
      DDRB |= ((1<<LED0) | (1<<LED3));
      if (index & 0x1 ) { PORTB |= (1<<LED0); PORTB &= ~(1<<LED3); }
      else { PORTB |= (1<<LED3); PORTB &= ~(1<<LED0); }
      break;
    default:
      PORTB = 0x00;
      break; 
  }
}

// 31250Hz
// Results in a refresh rate of ~54Hz
ISR(TIMER0_OVF_vect)
{
  static uint8_t led_cnt = 0;
  static uint8_t time_cnt = 0;
  
  // No conversion is in progress
  if (!(ADCSRA & (1<<ADSC)))
  {
    // Start conversion
    ADCSRA |= (1<<ADSC);
  }
  
  if (led_array[led_cnt] > time_cnt)
  {
    activateLED(led_cnt);
  }
  else
  {
    activateLED(-1);
  }
  
  if (time_cnt++ >= 48)
  {
    time_cnt = 0;
    led_cnt++;
    
    if (led_cnt >= 12)
    {
      led_cnt = 0;
    }
  }
}
