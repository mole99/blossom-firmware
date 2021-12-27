#include <buttons.h>

/*

When a button is pressed the capacitor is charged to a certain voltage level.
Using the 8 bits of the ADC this relates to:

Button 0: 192
Button 1: 128
Button 2: 64

The threshold are therefore defined as follows:

*/

#define BUTTON_0_TRESH 160
#define BUTTON_1_TRESH 96
#define BUTTON_2_TRESH 32

// This is the time the ADC value
// has to be in a certain threshold
// to register the button as pressed

#define DEAD_TIME 50 // ms

buttons_t buttons = {0};

void initADC()
{
  // Set Vcc as voltage reference
  // and left adjust the result
  // Set ADC2 (PB4) as input
  ADMUX = (1<<ADLAR) | (0b0010<<0);
  
  // Disable digital input for ADC2
  DIDR0 |= (1<<ADC2D);
  
  // Enable ADC and interrupt
  // Use 128 division factor
  ADCSRA = (1<<ADEN) | (1<<ADIE) | (0b111<<ADPS0);
}

ISR(ADC_vect)
{
  // Read the result (high byte)
  uint8_t result = ADCH;
  
  if (result >= BUTTON_0_TRESH)
  {
    // Reset time if newly pressed
    if (buttons.button_0.state == NOT_PRESSED)
    {
      buttons.button_0.time_ms = 0;
    }
    
    // The button must be pressed a certain time
    // to be activated
    if (buttons.button_0.time_ms >= DEAD_TIME)
    {
      buttons.button_0.state = PRESSED;
    }
    else
    {
      buttons.button_0.state = DEADTIME;
    }
    
    buttons.button_1.state = NOT_PRESSED;
    buttons.button_2.state = NOT_PRESSED;
  }
  else if (result >= BUTTON_1_TRESH)
  {
    // Reset time if newly pressed
    if (buttons.button_1.state == NOT_PRESSED)
    {
      buttons.button_1.time_ms = 0;
    }
    
    // The button must be pressed a certain time
    // to be activated
    if (buttons.button_1.time_ms >= DEAD_TIME)
    {
      buttons.button_1.state = PRESSED;
    }
    else
    {
      buttons.button_1.state = DEADTIME;
    }
    
    buttons.button_0.state = NOT_PRESSED;
    buttons.button_2.state = NOT_PRESSED;
  }
  else if (result >= BUTTON_2_TRESH)
  {
    // Reset time if newly pressed
    if (buttons.button_2.state == NOT_PRESSED)
    {
      buttons.button_2.time_ms = 0;
    }
    
    // The button must be pressed a certain time
    // to be activated
    if (buttons.button_2.time_ms >= DEAD_TIME)
    {
      buttons.button_2.state = PRESSED;
    }
    else
    {
      buttons.button_2.state = DEADTIME;
    }
    
    buttons.button_0.state = NOT_PRESSED;
    buttons.button_1.state = NOT_PRESSED;
  }
  else
  {
    // No button is pressed, return early
    buttons.button_0.state = NOT_PRESSED;
    buttons.button_1.state = NOT_PRESSED;
    buttons.button_2.state = NOT_PRESSED;
    return;
  }
  
  // Reset the inactive counter
  wdt_inactive_cnt = 0;
}

