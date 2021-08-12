#include <sequences.h>

void sequence0_heartBeatHard(uint8_t repetitions)
{
  while (repetitions-- > 0)
  {
    pattern0_pulseHard(200, 200);
    sleep_ms(100);
    pattern0_pulseHard(100, 100);
    sleep_ms(1000);
  }
}

void sequence1_heartBeatSoft(uint8_t repetitions)
{
  while (repetitions-- > 0)
  {
    pattern1_pulseSoft(200, 200);
    sleep_ms(100);
    pattern1_pulseSoft(100, 100);
    sleep_ms(1000);
  }
}

