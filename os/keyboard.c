
#include "globals.h"
#include "keyboard.h"
#include "messages.h"

#define KBD_PIN_LEFT		PC0
#define KBD_PIN_RIGHT		PC1
#define KBD_PIN_UP			PC2
#define KBD_PIN_DOWN		PC3
#define KBD_PIN_OK			PC4
//#define KBD_PIN_GND			PC5

#define KBD_PIN			PINC
#define KBD_PORT		PORTC
#define KBD_DDR			DDRC


#define KBD_MASK (_BV(KBD_PIN_UP)|_BV(KBD_PIN_DOWN)|_BV(KBD_PIN_LEFT)|_BV(KBD_PIN_RIGHT)|_BV(KBD_PIN_OK))



uint8_t lastKey,prevKey;
uint8_t kf1,kf2,kf3;

unsigned char getKeyCode(uint8_t ah) {
	if (!(ah & _BV(KBD_PIN_OK))) {
		return KEY_OK;
			
	}
	if (!(ah & _BV(KBD_PIN_UP))) {
		return KEY_UP;
	}
	if (!(ah & _BV(KBD_PIN_DOWN))) {
		return KEY_DOWN;
	}
	if (!(ah & _BV(KBD_PIN_LEFT))) {
		return KEY_LEFT;
	}
	if (!(ah & _BV(KBD_PIN_RIGHT))) {
		return KEY_RIGHT;
	}
	return 0;
}

unsigned char readKey(msg_par par) {
	kf3=kf2;
	kf2=kf1;
	kf1=getKeyCode(KBD_PIN & KBD_MASK);
	
	
	if ((kf2==kf1) && (kf3==kf2)) {
		prevKey = lastKey;
		lastKey = kf1;
	
		if (prevKey != lastKey) {
			sendMessage(MSG_KEY_PRESS, lastKey);
			killTimer(MSG_KEY_REPEAT);
			if (lastKey) {
				//setTimer(MSG_KEY_REPEAT,40,50);
			}
		}
	}
	
	
	return(0);
}

unsigned char repeatKey(msg_par par) {
	if (prevKey == lastKey) {
		sendMessage(MSG_KEY_PRESS, lastKey);
		if (par>5)
			setTimer(MSG_KEY_REPEAT,par-1,par);
		else
			setTimer(MSG_KEY_REPEAT,5,5);
	}

	
	return(0);
}



void  KBD_init() {
	KBD_PORT |= KBD_MASK;
	KBD_DDR &= ~ KBD_MASK;

	lastKey = 0;
	prevKey = 0;

	setHandler(MSG_KEY_SCAN, &readKey);
	setHandler(MSG_KEY_REPEAT, &repeatKey);

	setTimer(MSG_KEY_SCAN, 1, 1);
	
	
	
}
