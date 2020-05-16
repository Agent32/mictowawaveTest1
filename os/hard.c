
//#include "globals.h"
//
//#include "messages.h"

//#define KBD_PIN_GND			PC5


#include "hard.h"

 uint8_t testDiOn () {
	sbi(DDRB, PB0);
	sbi(PORTB, PB0);
	
	
	
	return 1;
}

uint8_t testDiOff () {

	
	cbi(DDRB, PB0);
	cbi(PORTB, PB0);
	
	return 1;
}


