/*
 * DisplayTest.c
 *
 * Created: 26.04.2018 12:49:47
 * Author : ArturD
 *ATMEGA8
 */ 


/*
����� � ������ � ����������� � ��������� �� "����" ��������

 */ 




#define F_CPU 8000000UL  // 8 MHz

#define sbi(var, mask)   ((var) |= (uint8_t)(1 << mask))
#define cbi(var, mask)   ((var) &= (uint8_t)~(1 << mask))

#include "globals.h"

#include "tc0.h"
#include "tc1.h"
#include "tc2.h"




#include "messages.h"
#include "messages.c"  
//#include "lcd.h"   
//#include "lcd.c"

#include "keyboard.h"
#include "keyboard.c"

#include "inicialize.c"

#include "i2c.h"
#include "hard.h"
#include "1307.h"
#include "menu.h"

#include "i2c.c"

#include "hard.c"


#include "1307.c"


#include "menu.c"


	











//������� ����� �������


 uint8_t testFun () {
	  /*
	 
	  */
	
	 if (PINB & (1 << PB0))
	 {
		  cbi(DDRB, PB0);
		  cbi(PORTB, PB0);
	 } 
	 else
	 {
		 	 sbi(DDRB, PB0);
		 	 sbi(PORTB, PB0);
	 }
	 

	
	
	 return 1;
	 
 }
 
 
 	


//����� ������ ��� ����������������� �������� � ������


int main(void)
{
	initMessages();
	KBD_init();
	lcd_init();  //���� ����
	//   TWI_MasterInit(50);
	 startMenu();
	 timeRead();  //������������� 1307
	
	
//	DDRB = _BV(PB0) | _BV(PB1) | _BV(PB2);

	
		setHandler(MSG_MENU_SELECT, &selectMenu);  //������ �������� ����
		//    setHandler(MSG_test, &testFun);
		setHandler(MSG_1307_ASK, &timeRead);    //������ ��������� ������� � ����� � 1307
		

	//	setHandler(MSG_TIMER_SEC , &secondOnGoin);   //������ �������
	//	 setTimer(MSG_TIMER_SEC, 0, 1000);
		
	//sendMessage(1, &testDiOn);
	
	
	
	//  sendMessage(MSG_MENU_SELECT, MENU_MODE2);
	  
	  
	  
	//selectMenu(MENU_MODE1);
	
  // setHandler(MSG_MENU_SELECT, &testDiOn);
   /* Replace with your application code */
	
	//sC(MSG_MENU_SELECT, sel);
	
	
  // setTimer(MSG_test, 0, 1000);
  

	
	
    while (1) 
    {  	
		 dispatchMessage();
		
    }
}





/*

���� ����������� � ���������, � ��������


��� ������� �� ����������� ��������.
���� �� 1703 � ������ �� 64 �������� 


*/