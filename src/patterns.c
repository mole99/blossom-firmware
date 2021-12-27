#include <patterns.h>

/*

Pattern ideas:

- 1. all Leds start at intensity 0, all increment at once, hard jump at the end
- 2. all Leds start at intensity 0, all increment at once, inverse direction at full intensity
- 3. led intensity = led index + offset, increase offset, hard jump
- 4. led intensity = led index + offset, increase offset, soft
- 5. stars: like 3 but multiply index i with e.g. 4

*/

/*
TODO
*/

void pattern0_bootupPattern(uint16_t duration_ms, uint16_t period_ms)
{
  uint8_t counter = 0;
  uint8_t current_led = 0;

  while (duration_ms-- > 0)
  {
    if (counter++ >= period_ms / NUM_LEDS)
    {
      for (uint16_t i=0; i<NUM_LEDS; i++)
      {
        led_array[i] = 0;
      }

      led_array[current_led] = MAX_INTENSITY;

      current_led++;
      
      current_led = current_led >= NUM_LEDS ? 0 : current_led;
      
      counter = 0;
    }
    sleep_ms(1);
  }
  
  for (uint16_t i=0; i<NUM_LEDS; i++)
  {
    led_array[i] = 0;
  }
}

void pattern0_pulseHard(uint16_t duration_ms, uint16_t period_ms)
{
  uint8_t counter = 0;
  uint8_t current_intensity = 0;

  while (duration_ms-- > 0)
  {
    if (counter++ >= period_ms / MAX_INTENSITY)
    {
  
      for (uint16_t i=0; i<NUM_LEDS; i++)
      {
        led_array[i] = intensity_lut[current_intensity];
      }
      
      current_intensity++;
      current_intensity = (current_intensity) % 16;
      
      counter = 0;
      
    }

    sleep_ms(1);
  }
  
  for (uint16_t i=0; i<NUM_LEDS; i++)
  {
    led_array[i] = 0;
  }
}

void pattern1_pulseSoft(uint16_t duration_ms, uint16_t period_ms)
{
  uint8_t counter = 0;
  uint8_t current_intensity = 0;

  while (duration_ms-- > 0)
  {
    if (counter++ >= period_ms / 30)
    {
  
      for (uint16_t i=0; i<NUM_LEDS; i++)
      {
        uint8_t led_intensity = current_intensity > MAX_INTENSITY ? 31 - current_intensity : current_intensity;
        led_array[i] = intensity_lut[led_intensity];
      }
      
      current_intensity++;
      current_intensity = (current_intensity) % 32;
      
      counter = 0;
      
    }

    sleep_ms(1);
  }
  
  for (uint16_t i=0; i<NUM_LEDS; i++)
  {
    led_array[i] = 0;
  }
}

void pattern2_fireRingHard(uint16_t duration_ms, uint16_t period_ms)
{
  uint8_t counter = 0;
  uint8_t current_offset = 0;

  while (duration_ms-- > 0)
  {
    if (counter++ >= period_ms / NUM_LEDS)
    {
      for (uint16_t i=0; i<NUM_LEDS; i++)
      {
        uint8_t led_intensity = ((i + current_offset ) % NUM_LEDS) * MAX_INTENSITY / NUM_LEDS;
        led_array[i] = intensity_lut[led_intensity % 16];
      }
      
      current_offset++;
      current_offset = (current_offset) % NUM_LEDS;
      
      counter = 0;
    }
    sleep_ms(1);
  }
  
  for (uint16_t i=0; i<NUM_LEDS; i++)
  {
    led_array[i] = 0;
  }
}

void pattern3_fireRingSoft(uint16_t duration_ms, uint16_t period_ms)
{
  uint8_t counter = 0;
  uint8_t current_offset = 0;

  while (duration_ms-- > 0)
  {
    if (counter++ >= period_ms / NUM_LEDS)
    {
      for (uint16_t i=0; i<NUM_LEDS; i++)
      {
        uint16_t current_intensity = ((i + current_offset) % NUM_LEDS) * 31 / NUM_LEDS;
      
        uint8_t led_intensity = current_intensity > MAX_INTENSITY ? 31 - current_intensity : current_intensity;
        led_array[i] = intensity_lut[led_intensity % 16];
      }
      
      current_offset++;
      current_offset = (current_offset) % NUM_LEDS;
      
      counter = 0;
    }
    sleep_ms(1);
  }
  
  for (uint16_t i=0; i<NUM_LEDS; i++)
  {
    led_array[i] = 0;
  }
}

void pattern4_starsHard(uint16_t duration_ms, uint16_t period_ms)
{
  uint8_t counter = 0;
  uint8_t current_offset = 0;

  while (duration_ms-- > 0)
  {
    if (counter++ >= period_ms / NUM_LEDS)
    {
      for (uint16_t i=0; i<NUM_LEDS; i++)
      {
        uint8_t led_intensity = ((i*9 + current_offset ) % NUM_LEDS) * MAX_INTENSITY / NUM_LEDS;
        led_array[i] = intensity_lut[led_intensity % 16];
      }
      
      current_offset++;
      current_offset = (current_offset) % NUM_LEDS;
      
      counter = 0;
    }
    sleep_ms(1);
  }
  
  for (uint16_t i=0; i<NUM_LEDS; i++)
  {
    led_array[i] = 0;
  }
}

void pattern99_lightning(uint16_t duration_ms, uint16_t period_ms)
{
  uint8_t counter = 0;
  uint8_t current_intensity = 0;

  while (duration_ms-- > 0)
  {
    if (counter++ >= period_ms / 16)
    {
  
      for (uint16_t i=0; i<NUM_LEDS; i++)
      {
        led_array[i] = intensity_lut[current_intensity];
      }
      
      current_intensity++;
      current_intensity = (current_intensity) % 16;
      
      counter = 0;
      
    }

    sleep_ms(1);
    
    for (uint16_t i=0; i<NUM_LEDS; i++)
    {
      led_array[i] = 0;
    }
  }
}
