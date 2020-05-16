#ifndef _MENU_H_
#define _MENU_H_

enum {
    MENU_CANCEL=1,
    MENU_RESET,
    MENU_settime1,
    MENU_settime2,
    MENU_settime3,
    MENU_SENS1,
    MENU_SENS2,
	MENU_TIME,
    MENU_WARM,
    MENU_PROCESS
};

uint8_t startMenu();
void initMenu();

uint8_t TimeConf();
uint8_t Timedisplay();
uint8_t secondOnGoin();
uint8_t HeatMicro();
uint8_t EditDay ();
uint8_t editH ();
uint8_t EditDate ();
#endif
