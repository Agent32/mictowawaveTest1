/*
 * globals.h
 *
 *	Тут описываются все инклюды, общие для всего проекта. Чтобы их каждый раз не определять в каждом файле.
 *
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <stdio.h>
#include <avr/eeprom.h>

//#define NULL	0
#define FALSE	0
#define TRUE	(!FALSE)

#define Enibble 0xf0
#define Jnibble 0xf


//set bit - using bitwise OR operator
#define sbi(x,y) x |= _BV(y)   //x- что у - где  sbi (ASSR,AS2);
//clear bit - using bitwise AND operator
#define cbi(x,y) x &= ~(_BV(y))

#define assNOP asm("nop")
#define assCLI asm("cli")
#define assSEI asm("sei")

//переменные используемые в некоторых функциях.


uint8_t takt=0;  //переменная которая меняет состояние раз в секунду. НАДО ЗАГНАТЬ ЕЁ В БИТ. СТРУКТУРУ
 uint32_t test2=82299;

 struct byteStruct {
	 unsigned  bFunctEnter: 1;
	 unsigned  takt: 1;
	 unsigned  doorO: 1;
	  unsigned  smokeD: 1;
	  unsigned  TimerBit: 16;
	 } biteCode = {0,0,0,0,0};


uint8_t delay_T1=0; 

#endif /* GLOBALS_H_ */

