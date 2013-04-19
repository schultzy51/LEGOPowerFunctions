/*
example for the 8275 bulldozer

*/
#include <legopowerfunctions.h>

// IR led on port 13
LEGOPowerFunctions lego(13);

int timeout, count;

void setup()
{
}

void loop()
{
  timeout = 5; // 5 secs
  count = 0;
  while(timeout > 0)
  {
    lego.ComboPWM(PWM_REV4, PWM_FWD4, CH1); // 50% speed
    delay(100);
    if (count++ == 10)
    {
      timeout--;
      count = 0;
    }
  }
  lego.ComboPWM(PWM_FLT, PWM_FLT, CH1); // stop
  delay(1000);
  timeout = 3; // 5 secs
  count = 0;
  while(timeout > 0)
  {
    lego.ComboMode(RED_FWD, BLUE_FWD, CH1);  // turn
    delay(100);
    if (count++ == 10)
    {
      timeout--;
      count = 0;
    }
  } 
}
