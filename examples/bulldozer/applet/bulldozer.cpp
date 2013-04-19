/*
example for the 8275 bulldozer

*/
#include <legopowerfunctions.h>

// IR led on port 13
#include "WProgram.h"
void setup();
void loop();
LEGOPowerFunctions lego(9);


void setup()
{
}

void loop()
{
  lego.ComboMode(BLUE_FLT, RED_FWD, CH1);
  //delay(100);
}

int main(void)
{
	init();

	setup();
    
	for (;;)
		loop();
        
	return 0;
}

