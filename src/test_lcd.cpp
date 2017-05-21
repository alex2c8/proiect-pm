#include "UTFT.h"

extern uint8_t SmallFont[];

int main(void)
{
	UTFT utft = UTFT();
	
	utft.setFont(SmallFont);
	
	//char str[] = "Hello, world!";

	utft.InitLCD(0);
	
	_delay_ms(50);
	utft.fillScr(0, 0, 0);
	_delay_ms(50);
	
	while (1) {
		// N -> A
		//utft.drawRoundRect(50, 50, 100, 100);
		utft.print("ABCDE", 50, 50, 90);
		_delay_ms(100);
	}
	
	return 0;
}