#include "globals.h"
#include "menu.h"
#include "keyboard.h"
#include "messages.h"
#include "lcd.h"
#include "hard.h"
 
 
typedef struct PROGMEM{
	void       *Next;
	void       *Previous;
	void       *Parent;
	void       *Child;
	uint8_t     Select;
	char  Text[10];
} menuItem;

menuItem* selectedMenuItem; // ������� ����� ����

menuItem* menuStack[10];
volatile uint8_t menuStackTop;


/*------------------- ������� �����-------------------  */
//#define NULL_ENTRY Null_Menu
#define NULL_FUNC  (void*)0
#define NULL_TEXT  0x00

/*------------------- ������� ����-------------------  */
#define DECLARE_ITEM 	const PROGMEM menuItem
#define MAKE_MENU		const PROGMEM menuItem

/****************************************************************************
 ���������� ���������� ��� ����� �����������
****************************************************************************/
	
 uint8_t pikr () {
	 sbi(DDRB, PB0);
	 sbi(PORTB, PB0);
	 
	 
	 
	 return 1;
 }

int8_t timeToChange=0; //���� ��� �������
uint8_t changeTimesetting=0; //

/* #define MAKE_MENU(Name, Next, Previous, Parent, Child, Select, Text) \
    extern menuItem Next;     
	extern menuItem Previous; 
	extern menuItem Parent;   
	extern menuItem Child;  
	menuItem Name = {(void*)&Next, (void*)&Previous, (void*)&Parent, (void*)&Child, (uint8_t)Select, { Text }}  */
		
/****************************************************************************
 �������� ���� 
****************************************************************************/

#define PREVIOUS   ((menuItem*)pgm_read_word(&selectedMenuItem->Previous))
#define NEXT       ((menuItem*)pgm_read_word(&selectedMenuItem->Next))
#define PARENT     ((menuItem*)pgm_read_word(&selectedMenuItem->Parent))
#define CHILD      ((menuItem*)pgm_read_word(&selectedMenuItem->Child))
#define SELECT		(pgm_read_byte(&selectedMenuItem->Select))

const char strNULL[] PROGMEM = "";
DECLARE_ITEM   NULL_ENTRY = {NULL_FUNC, NULL_FUNC, NULL_FUNC, NULL_FUNC, NULL_TEXT}; 
	DECLARE_ITEM main1;
	DECLARE_ITEM main2;
	DECLARE_ITEM main3;
	DECLARE_ITEM child1;
	DECLARE_ITEM child2;
	DECLARE_ITEM child3;
//#define NULL_ENTRY Null_Menu
//menuItem        Null_Menu = {(void*)0, (void*)0, (void*)0, (void*)0, 0, {0x00}};


//                 NEXT,      PREVIOUS     PARENT,     CHILD     SELEST
MAKE_MENU main1 = { &main2,    &main3,      &main1,       &child1,       0,   "Settings"};
MAKE_MENU main2={  &main3,    &main1,      &main1,       NULL,       MENU_WARM, "Heat"};  
MAKE_MENU main3={  &main1 ,   &main2,      &main1,		NULL,   MENU_TIME, "Time"};
	
	// ������� 
MAKE_MENU child1={  &child2 ,  &child2,      &main1,		NULL,  MENU_settime1 , "Time"};
MAKE_MENU child2={  &child3 ,  &child3,      &main1,		NULL,   MENU_settime2, "Day"};	//���� � ���� �������
MAKE_MENU child3={  &child1 ,  &child1,      &main1,		NULL,   MENU_settime3, "Data"};	
/*// ������� ������
MAKE_MENU child31=( &child34,    NULL_ENTRY,  NULL_ENTRY,     NULL_ENTRY,   MENU_MODE1, "Mode 1");
MAKE_MENU child32=( &child31,    NULL_ENTRY,      NULL_ENTRY,     NULL_ENTRY,   MENU_MODE2, "Mode 2");
MAKE_MENU child33=(   &child32,NULL_ENTRY,      NULL_ENTRY,     NULL_ENTRY,   MENU_MODE3, "Mode 3");

// ������� ���������
MAKE_MENU child34=(  &child33,    NULL_ENTRY,  NULL_ENTRY,     NULL_ENTRY,       0, "Pressure");
MAKE_MENU child311=( &child312,NULL_ENTRY,      NULL_ENTRY,     NULL_ENTRY,       0, "Time");

// ������� ��������
MAKE_MENU child312=(  &child312,    NULL_ENTRY,  NULL_ENTRY,     NULL_ENTRY,   MENU_SENS1, "Sensor 1");
MAKE_MENU sidePun=( &child311,&main1,     NULL,     NULL_ENTRY,   MENU_SENS2, "Sensor 2");

// ������� �����
//MAKE_MENU(m_s5i1,  m_s5i2,    NULL_ENTRY,  m_s3i2,     NULL_ENTRY,   MENU_WARM, "Warm");
//MAKE_MENU(m_s5i2,  NULL_ENTRY,m_s5i1,      m_s3i2,     NULL_ENTRY,   MENU_PROCESS, "Process");
*/

void menuChange(menuItem* NewMenu)
{
	if ((void*)NewMenu == (void*)&NULL_ENTRY)
	  return;

	selectedMenuItem = NewMenu;
}

unsigned char dispMenu(msg_par par) {
	menuItem* tempMenu;

	lcd_clrscr(1);
	// ������ ������ - ���������. ��� ����� ���� �������� ������
	lcd_gotoxy(1,0);
	
	
	
	
	tempMenu = (menuItem*)pgm_read_word(&selectedMenuItem->Parent);
	
	
	
	
	if ((void*)tempMenu == (void*)&NULL_ENTRY) { // �� �� ������� ������
		lcd_puts_p(PSTR("MENU:"));
		} else {
		//lcd_puts_p((char *)tempMenu->Text);
		lcd_puts_p(PSTR("MENU:"));
	}

	lcd_clrscr(2);
	//������ ������ - ������� ����� ����
	lcd_gotoxy(2,1);
	lcd_puts_p((char *)selectedMenuItem->Text);

	return (1);
}

uint8_t menuKey(msg_par par) {
	switch (par) {
	case 0: {
		return 1;
	}
	case KEY_LEFT: {
		menuChange(PREVIOUS);
		break;
	}
	case KEY_RIGHT: {
		menuChange(NEXT);
		break;
	}
	case KEY_DOWN:
		;
	case KEY_OK:
		{ // ����� ������
			
			uint8_t sel;
			sel = SELECT;
			if (sel != 0) {
				
			sendMessage(MSG_MENU_SELECT, sel);
			
				


				killHandler(MSG_KEY_PRESS, &menuKey);
				killHandler(MSG_DISP_REFRESH, &dispMenu);
			

				return (1);
			} else {
				menuChange(CHILD);
			}
			break;
		}
	case KEY_UP: { // ������ ������ (�������)
		menuChange(PARENT);
	}
	}
	dispMenu(0);
	return (1);
}

uint8_t startMenu() {
	selectedMenuItem = (menuItem*)&main1;

	dispMenu(0);
	setHandler(MSG_KEY_PRESS, &menuKey);
	setHandler(MSG_DISP_REFRESH, &dispMenu);
	return (0);
}

void initMenu() {
	lcd_init();
}

/****************************************************************************
 ������� ������ �������
****************************************************************************/

 volatile  uint8_t selestChar=0;  //��������� ������ �� ����������, ��������� ���� ������ �������� ������ ��� ������ ����� � �������� ����/�����
 volatile  uint8_t timeToSend = 0;   //((timeData[4]& 0xf0))  //����� ��� �������� ��� ������ ����� ����� ������ ���� �����


//-----------------------------------������� ������� � ����������� �� �������---------------------------------


uint8_t selectMenu(msg_par par) {
	
	switch (par) {
		case MENU_settime1: {  
			killHandler(MSG_KEY_PRESS, &selectMenu);	
			setTimer(MSG_KEY_PRESS, 0, 200);
			setTimer(MSG_1307_ASK, 0, 200);
			setHandler(MSG_KEY_PRESS, &editH);
			
			
				setHandler(MSG_TIMER_SEC , &secondOnGoin);
				setTimer(MSG_TIMER_SEC, 0, 1000);   //������ �������
			
			
			 break; }  // ��������� �������
		
		
		
		
		
		
		case MENU_settime2: { // ��������� � ���
			
			
		 killHandler(MSG_KEY_PRESS, &selectMenu);
		 setTimer(MSG_KEY_PRESS, 0, 200);
		 setTimer(MSG_1307_ASK, 0, 200);
		 setHandler(MSG_KEY_PRESS, &EditDay);
		 
		 
		 setHandler(MSG_TIMER_SEC , &secondOnGoin);
		 setTimer(MSG_TIMER_SEC, 0, 1000);   //������ �������
		 
		 
			
			
			break;
			
			
		}  //�������2
		
		
		
		case MENU_settime3: { 
			
			
			
		 killHandler(MSG_KEY_PRESS, &selectMenu);
		 setTimer(MSG_KEY_PRESS, 0, 200);
		 setTimer(MSG_1307_ASK, 0, 200);
		 setHandler(MSG_KEY_PRESS, &EditDate);
		 
		 
		 setHandler(MSG_TIMER_SEC , &secondOnGoin);
		 setTimer(MSG_TIMER_SEC, 0, 1000);   //������ �������
			
			
			
			
		break;
			
		}
		
		case MENU_WARM: {  lcd_clrscr(2);
			lcd_gotoxy(3,1); lcd_puts_p(PSTR("HEAT PROG"));
			
			setHandler(MSG_TIMER_SEC , &secondOnGoin); 
			setTimer(MSG_TIMER_SEC, 0, 1000);   //������ �������
			
			setHandler(MSG_KEY_PRESS , &HeatMicro);  
			setTimer(MSG_KEY_PRESS, 0, 200);
			
			
			
			break;
		}  //������� �������
		
		
		case MENU_TIME: {   
			setTimer(MSG_KEY_PRESS, 0, 200);
			setTimer(MSG_1307_ASK, 0, 200);
			
			setHandler(MSG_KEY_PRESS, &Timedisplay); 
			break;
			
		}  //������� �������
		
		
		
		
		
		case MENU_RESET: { // ��� ���������� ����� ������ Reset
		break;
			//break;
		}
		// ... � ��� ����� �� ���� �������
		
	}   //����� �����

	// ����� ������ ������������ � ������� ����.
	//startMenu();
	return 1;
}  // ����� ������


//���� ���������� ��� ������� �� ������� � ��������� ����
//����� ������ ����, ����� �����, ����� ������.
//������ ����  ���������� �������������� ����� � ������ � 1307
//��������� �� ������� �������, ����� ������������� ��������� ����� ��������� �� ������� ��� ������
//��������� ����� ������ ������� ���������� �����, �� ����� ������� ������ �� �������, � ������������� ��� ������� ��

//-----------------------------------��������� �������---------------------------------


uint8_t TimeConf (msg_par par) {
	
/*

if (selestChar>3) {selestChar=1;}
	if (selestChar==0) {selestChar=3;}

lcd_clrscr(1);
lcd_clrscr(2);

if ( selestChar==1 && biteCode.takt==1 ) { }
	     
	  else {  lcd_gotoxy(1,0);
	  lcd_put_hex((uint8_t *)timeData[6]);
	  lcd_put_hex((uint8_t *)timeData[7]);
	  lcd_put_hex((uint8_t *)timeData[8]);}

lcd_gotoxy(7,0);
if ( selestChar==2 &&  biteCode.takt==1 ) { }  
	
	else { 
		//���� ������

		switch (timeData[5]){
			
			case 1 : { lcd_puts_p(PSTR("  Sun"));  break;}   //�����
			case 2:  {   lcd_puts_p(PSTR("  Mon")); break; }   //��
			
			case 3: {  lcd_puts_p(PSTR(" Tue"));   break; }
			case 4: {  lcd_puts_p(PSTR("  Wed"));    break; }   //��
			
			case 5: {   lcd_puts_p(PSTR("  Thu"));   break; }   //��
			case 6: {  lcd_puts_p(PSTR("  Fri"));    break; }
			case 7: {  lcd_puts_p(PSTR("  Sat"));    break; }   //��
			default: return;}
		
	}
	
	


if (  selestChar==3 &&  biteCode.takt==1 ) {}  
	else {
		
		lcd_gotoxy(4,1);
		lcd_put_hex((uint8_t *)timeData[4]);
		lcd_put_hex((uint8_t *)timeData[3]);
		lcd_put_hex((uint8_t *)timeData[2]);
	} 
	
	
	
	
	switch (par) {
		
		//------------------
		
			case 0: {
				return 1;
			}
			case KEY_LEFT: {
				
				  selestChar--;
				break;
			}
			case KEY_RIGHT: {
				 selestChar++;
				break;
			}
			case KEY_DOWN:
			;
			case KEY_OK:
			{ // ����� ������
				
					killHandler(MSG_KEY_PRESS, &TimeConf);   killTimer(MSG_KEY_PRESS);
					killHandler(MSG_KEY_PRESS, &TimeConf);   killTimer(MSG_KEY_PRESS);  killTimer(MSG_1307_ASK);   killTimer(MSG_TIMER_SEC);
				
				switch (selestChar) 
				{
				case 1: {setHandler(MSG_KEY_PRESS , &editH);
					setTimer(MSG_KEY_PRESS, 0, 200); }  //�������������� �������
					case 2: {}   //�������������� ���
						case 3: {}   //�������������� ����
				}
					
					//editH();  lcd_puts_p(PSTR("FFFFFFFFFFFFF"));
					
					
					
				
				break;
			}
			case KEY_UP: { // ������ ������ (�������)
				killHandler(MSG_KEY_PRESS, &TimeConf);   killTimer(MSG_KEY_PRESS);  killTimer(MSG_1307_ASK);   killTimer(MSG_TIMER_SEC);
				
				startMenu();
				
				
			}
		}  //����� �����
		
		return (1);  */
	}  //���� �������
	

		
		//-----------------
		
	

//----------------------------------��������� �������---------------------------------


uint8_t Timedisplay (msg_par par) 
{
	lcd_clrscr(1);
	lcd_gotoxy(1,0);
	lcd_put_hex((uint8_t *)timeData[6]);
	lcd_put_hex((uint8_t *)timeData[7]);
	lcd_put_hex((uint8_t *)timeData[8]);

	//���� ������
	switch (timeData[5]){
		
		case 1 : { lcd_puts_p(PSTR("  Sunday"));  break;}   //�����
		case 2:  {   lcd_puts_p(PSTR("  Monday")); break; }   //��
		
		case 3: {  lcd_puts_p(PSTR("  Tuesday"));   break; }
		case 4: {  lcd_puts_p(PSTR("  Wednesday"));    break; }   //��
		
		case 5: {   lcd_puts_p(PSTR("  Thursday"));   break; }   //��
		case 6: {  lcd_puts_p(PSTR("  Friday"));    break; }
		case 7: {  lcd_puts_p(PSTR("  Saturday"));    break; }   //��
		
	default: return;  }

	lcd_clrscr(2);
	lcd_gotoxy(4,1);
	lcd_put_hex((uint8_t *)timeData[4]);
	lcd_put_hex((uint8_t *)timeData[3]);
	lcd_put_hex((uint8_t *)timeData[2]);

	
	switch (par) {
		case 0: { 		  break;     }
		
		case KEY_LEFT: {		break;	}
		case KEY_RIGHT:  {    break;   }
		
		
		
		case KEY_DOWN:  {    break;   }
		
		
		case KEY_OK:	{  break; }	 // ����� ������
		
		
		case KEY_UP:// ������ ������ (�������)
		{
			killHandler(MSG_KEY_PRESS, &Timedisplay);   killTimer(MSG_KEY_PRESS);  killTimer(MSG_1307_ASK);
			
			startMenu();
		break;    }
		
		
		
	}  //�����  ����
	

}


//----------------------------------  ������ ---------------------------------

uint8_t secondOnGoin() {
	
	biteCode.TimerBit++;
	if ( biteCode.TimerBit>59)
	{ biteCode.TimerBit = 0;} else { }
	
	if (biteCode.takt==1)
	{biteCode.takt=0; } else { biteCode.takt=1;	}
	
	
	return 1;
}


//--------------------------------������---------------------



uint8_t HeatMicro (msg_par par) {
	
	

	lcd_clrscr(1);
	lcd_gotoxy(5,0);
	lcd_put_dec( biteCode.TimerBit);
	
	
	switch (par) {
		case 0: { 				  break;     }
		
		case KEY_LEFT: {
			
			
			
			break;
		}
		case KEY_RIGHT:  {    break;   }
		
		
		
		case KEY_DOWN:  {    break;   }
		
		
		case KEY_OK:
		{  break; }	 // ����� ������
		
		
		case KEY_UP:// ������ ������ (�������)
		{
			killHandler(MSG_KEY_PRESS, &HeatMicro);   killTimer(MSG_KEY_PRESS);   killTimer(MSG_TIMER_SEC);  
			
			startMenu();
		break;    }
		
		
		
	}  //�����  ����
	
}  //����� ������



//--------------------------------�������� ����/�����/���---------------------


//���������� �������������� ����� �������


uint8_t EditDay (msg_par par) {
 lcd_clrscr(1);
	 lcd_clrscr(2);
lcd_gotoxy(1,0);  lcd_puts_p(PSTR("Chose Day"));
if (selestChar==0){selestChar=1;}





lcd_gotoxy(2,1);  // dd  mm yy

switch (selestChar){
	
	case 1 : { lcd_puts_p(PSTR("  Sunday"));  break;}   //�����
	case 2:  {   lcd_puts_p(PSTR("  Monday")); break; }   //��
	
	case 3: {  lcd_puts_p(PSTR("  Tuesday"));   break; }
	case 4: {  lcd_puts_p(PSTR("  Wednesday"));    break; }   //��
	
	case 5: {   lcd_puts_p(PSTR("  Thursday"));   break; }   //��
	case 6: {  lcd_puts_p(PSTR("  Friday"));    break; }
	case 7: {  lcd_puts_p(PSTR("  Saturday"));    break; }   //��
	
default: return;  }
	
	

switch (par) {
	
	//------------------
	
	case 0: {
		return 1;
	}
	case KEY_LEFT: { //����� ���������
		
		
		selestChar--;
		if (selestChar==0){selestChar=7;} else{}
		break;
	}
	case KEY_RIGHT: { //����� ���������
		
		
		selestChar++;
		if (selestChar>7){selestChar=1;} else{}
		break;
	}
	case KEY_DOWN:
	;
	case KEY_OK:
	{ // �������� ��������� ������
		

		
	changedataSelest(6,selestChar);
		
		
		break;
	}
	case KEY_UP: { // ��������� � �����
		
		
		
		killHandler(MSG_KEY_PRESS, &TimeConf);   killTimer(MSG_KEY_PRESS);  killTimer(MSG_1307_ASK);   killTimer(MSG_TIMER_SEC);
		
		startMenu();
		
		
	}
}  //����� �����

	
	 return 1;
}



//---------------               ����             --------------- 

//������ ���� - ��������� ���������� �����, ����� ����� ����������� ���������� �� �� ��� ���� ��� ���

 uint8_t editH (msg_par par) {
	  /*
	 
	  */
	
	
	 lcd_clrscr(1);
	 lcd_clrscr(2);
lcd_gotoxy(1,0);  lcd_puts_p(PSTR("Enter Time"));






lcd_gotoxy(4,1);  // hh mm ss

//�������� ����
	lcd_put_hex((uint8_t *)timeData[4]);  //  4 5
	lcd_put_hex((uint8_t *)timeData[3]);  // 6 7
	lcd_put_hex((uint8_t *)timeData[2]);   //  8 9
	//lcd_puts ("z");
	
	
	
switch (selestChar){
	
	case 0 : { if (timeToChange>2){timeToChange=0;}; lcd_gotoxy(4,1);  if (takt)
	{  lcd_put_dec(timeToChange);  } else { lcd_puts ("z");}  lcd_gotoxy(4,1); break;}
	case 1:  { if (timeToChange>9){timeToChange=0;};    lcd_gotoxy(5,1);  lcd_put_dec(timeToChange); lcd_gotoxy(5,1);  break; }
	
	case 2: { if (timeToChange>5){timeToChange=0;  }; lcd_gotoxy(6,1); lcd_put_dec(timeToChange);  lcd_gotoxy(6,1); break; }
	case 3: { if (timeToChange>9){timeToChange=0  ;}; lcd_gotoxy(7,1); lcd_put_dec(timeToChange);  lcd_gotoxy(7,1); break; }
	
	case 4: { if (timeToChange>5){timeToChange=0;}; lcd_gotoxy(8,1); lcd_put_dec(timeToChange);  lcd_gotoxy(8,1); break; }
	case 5: { if (timeToChange>9){timeToChange=0;};  lcd_gotoxy(9,1);  lcd_put_dec(timeToChange);  lcd_gotoxy(9,1); break; }
	
default: return;  }	






//������� ���������� �� ���������, ������� ����� ����������� � ������ ��������.
//������������� ����� �������� �� �����, �������� ���� ������ ������ �����.
	//lcd_gotoxy(4,1);
	//lcd_put_hex((uint8_t *)timeData[4]);
	//lcd_put_hex((uint8_t *)timeData[3]);
	//lcd_put_hex((uint8_t *)timeData[2]);


switch (par) {
	
	//------------------
	
	case 0: {
		return 1;
	}
	case KEY_LEFT: { //����� ���������
		
selestChar++;
if (selestChar>5) {selestChar=0;}
		
		switch (selestChar){
			
			case 0: {  timeToChange = converterTenSix(timeData[4]& Enibble);  break; }      //�������� ���  �������� - ������ �����, ����� � - ������return 1;  } timeData[2] = (timeData[2]& 0xf0) |timeToChange;
			case 1: {   timeToChange = timeData[4]& Jnibble;   break;   }
			case 2: { timeToChange = converterTenSix(timeData[3]& Enibble);  break; }   //������ ���
			case 3: { timeToChange = timeData[3]& Jnibble;   break; }  //������
			case 4: { timeToChange = converterTenSix(timeData[2]& Enibble); break; }  //������ ���
			case 5: { timeToChange = timeData[2]& Jnibble;  break;  }  //c��
			
			
			default: {};}
		
		
		
			
		
		//timeToChange--;
		//if (timeToChange<0){timeToChange=9;} else{}
		break;
	}
	case KEY_RIGHT: { //����� ���������
		
		
		
		timeToChange++;
		if (timeToChange>9){timeToChange=0;} else{}
		break;
	}
	case KEY_DOWN:
	;
	case KEY_OK:
	{ // �������� ��������� ������
		
	//������ ������ � ��������
	
	/*
switch (selestChar){
	
	case 0: { timeData[4] = (timeToChange<<4)| (timeData[4]& Jnibble);  break; }      //�������� ���  �������� - ������ �����, ����� � - ������return 1;  } timeData[2] = (timeData[2]& 0xf0) |timeToChange;
	case 1: {   timeData[4] = (timeData[4]& Enibble) |timeToChange;    break;   }
	case 2: {timeData[3] = (timeToChange<<4)| (timeData[3]& Jnibble);  break; }   //������ ���
	case 3: {timeData[3] = (timeData[3]& Enibble) |timeToChange;    break; }  //������
	case 4: { timeData[2] = (timeToChange<<4)| (timeData[2]& Jnibble);  break; }  //������ ���
	case 5: { timeData[2] = (timeData[2]& Enibble) |timeToChange;    break;  }  //c��
	
	
	default: {};}  */
		
	changeClockSelest(selestChar,timeToChange);
		
	
		
		
		
		break;
	}
	case KEY_UP: { // ��������� � �����
		
		
		
		killHandler(MSG_KEY_PRESS, &TimeConf);   killTimer(MSG_KEY_PRESS);  killTimer(MSG_1307_ASK);   killTimer(MSG_TIMER_SEC);
		
		startMenu();
		
		
	}
}  //����� �����

	
	 return 1;
	 
 }
 
 
 
 
 
//---------------               ����             --------------- 
 
 
 uint8_t EditDate (msg_par par) {
	 
	 lcd_clrscr(1);
	 lcd_clrscr(2);
lcd_gotoxy(1,0);  lcd_puts_p(PSTR("Enter Date"));






lcd_gotoxy(4,1);  // dd  mm yy
	lcd_put_hex((uint8_t *)timeData[6]);  //  4 5
	lcd_put_hex((uint8_t *)timeData[7]);  // 6 7
	lcd_put_hex((uint8_t *)timeData[8]);   //  8 9
	
	
switch (selestChar){
	
	case 0 : { if (timeToChange>3){timeToChange=0;}; lcd_gotoxy(4,1);  lcd_put_dec(timeToChange); lcd_gotoxy(4,1); break;}
	case 1:  { if (timeToChange>9  ){timeToChange=0;};    lcd_gotoxy(5,1);  lcd_put_dec(timeToChange); lcd_gotoxy(5,1);  break; }
	
	case 2: { if (timeToChange>1){timeToChange=0;  }; lcd_gotoxy(6,1); lcd_put_dec(timeToChange);  lcd_gotoxy(6,1); break; }
	case 3: { if (timeToChange>9){timeToChange=0  ;}; lcd_gotoxy(7,1); lcd_put_dec(timeToChange);  lcd_gotoxy(7,1); break; }
	
	case 4: { if (timeToChange>9){timeToChange=0;}; lcd_gotoxy(8,1); lcd_put_dec(timeToChange);  lcd_gotoxy(8,1); break; }
	case 5: { if (timeToChange>9){timeToChange=0;};  lcd_gotoxy(9,1);  lcd_put_dec(timeToChange);  lcd_gotoxy(9,1); break; }
	
default: return;  }	





switch (par) {
	
	//------------------
	
	case 0: {
		return 1;
	}
	case KEY_LEFT: { //����� ���������
		
		
		timeToChange--;
		if (timeToChange<0){timeToChange=9;} else{}
		break;
	}
	case KEY_RIGHT: { //����� ���������
		
		
		timeToChange++;
		if (timeToChange>9){timeToChange=0;} else{}
		break;
	}
	case KEY_DOWN:
	;
	case KEY_OK:
	{ // �������� ��������� ������
		
	//������ ������ � ��������
	
	/*
switch (selestChar){
	
	case 0: { timeData[4] = (timeToChange<<4)| (timeData[4]& Jnibble);  break; }      //�������� ���  �������� - ������ �����, ����� � - ������return 1;  } timeData[2] = (timeData[2]& 0xf0) |timeToChange;
	case 1: {   timeData[4] = (timeData[4]& Enibble) |timeToChange;    break;   }
	case 2: {timeData[3] = (timeToChange<<4)| (timeData[3]& Jnibble);  break; }   //������ ���
	case 3: {timeData[3] = (timeData[3]& Enibble) |timeToChange;    break; }  //������
	case 4: { timeData[2] = (timeToChange<<4)| (timeData[2]& Jnibble);  break; }  //������ ���
	case 5: { timeData[2] = (timeData[2]& Enibble) |timeToChange;    break;  }  //c��
	
	
	default: {};}  */
		
	changedataSelest(selestChar,timeToChange);
		
		selestChar++;
		if (selestChar>5) {selestChar=0;}
		
		
		
		break;
	}
	case KEY_UP: { //  � �����
		
		
		
		killHandler(MSG_KEY_PRESS, &TimeConf);   killTimer(MSG_KEY_PRESS);  killTimer(MSG_1307_ASK);   killTimer(MSG_TIMER_SEC);
		
		startMenu();
		
		
	}
}  //����� �����

	
	 return 1;
		 
	 }