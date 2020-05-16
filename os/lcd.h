#ifndef _LCH_H_
#define _LCD_H_ 1

#define LCD_A0  PD0
#define LCD_RW  PD1
#define LCD_E   PD2
#define LCD_DB4 PD4
#define LCD_DB5 PD5
#define LCD_DB6 PD6
#define LCD_DB7 PD7
#define DISPPORT PORTD 
#define DISPDDR DDRD



void lcd_write(unsigned char codeA);
unsigned char lcd_readStatus();
void lcd_putc(unsigned char ch);
void lcd_put_hex(unsigned char ch);
void lcd_init(void);
void lcd_puts(char *str);
void lcd_puts_p(char *str);
void lcd_gotoxy(unsigned char x, unsigned char y);
void lcd_clrscr(unsigned char data);




void lcd_write(unsigned char codeA)
{
	//cli();
	DISPPORT &= ~( _BV(LCD_A0) | _BV(LCD_RW) );
	_delay_us(10);
	DISPPORT |= _BV(LCD_E); // строб
	DISPPORT |= codeA; 
	_delay_us(10);
	DISPPORT &= ~_BV(LCD_E); // ~строб
	_delay_us(10);
	DISPPORT ^= codeA; 
	_delay_us(10);
	//sei();
}

unsigned char lcd_readStatus()
{
	char BS;

	DISPPORT |= ( _BV(LCD_RW) );
	_delay_us(10);
	DISPDDR &= ~( _BV(LCD_DB7) | _BV(LCD_DB6) | _BV(LCD_DB5) | _BV(LCD_DB4) );
	DISPPORT |= ( _BV(LCD_E) ); // строб
	_delay_us(10);
	DISPPORT &= ~_BV(LCD_E); // ~строб
	BS = (DISPPORT & _BV(LCD_DB7)) >> LCD_DB7;  //NEN
	_delay_us(10);
	DISPPORT |= _BV(LCD_E); // строб
	_delay_us(10);
	DISPPORT &= ~_BV(LCD_E); // ~строб
	_delay_us(10);

	DISPDDR |= ( _BV(LCD_DB7) | _BV(LCD_DB6) | _BV(LCD_DB5) | _BV(LCD_DB4) );
	DISPPORT &= ~( _BV(LCD_DB7) | _BV(LCD_DB6) | _BV(LCD_DB5) | _BV(LCD_DB4) | _BV(LCD_RW));
	_delay_us(2);

	return BS;
}

void lcd_putc(unsigned char ch)
{
	//while (lcd_readStatus()) {}

	lcd_write(_BV(LCD_A0) 
		| ((ch & _BV(7)) >> 7)	<< LCD_DB7
		| ((ch & _BV(6)) >> 6)	<< LCD_DB6
		| ((ch & _BV(5)) >> 5)	<< LCD_DB5
		| ((ch & _BV(4)) >> 4)	<< LCD_DB4
	);
	lcd_write(_BV(LCD_A0) 
		| ((ch & _BV(3)) >> 3)	<< LCD_DB7
		| ((ch & _BV(2)) >> 2)	<< LCD_DB6
		| ((ch & _BV(1)) >> 1)	<< LCD_DB5
		| (ch & 1) 		<< LCD_DB4
	);
	_delay_us(2);
}

void lcd_put_hex(unsigned char ch)
{
	unsigned char s;
	s = (ch & 0xf0) >> 4;
	if (s<10)
		lcd_putc('0'+s);
	else
		lcd_putc('A'+s-10);

	s = (ch & 0x0f);
	if (s<10)
		lcd_putc('0'+s);
	else
		lcd_putc('A'+s-10);
}

void lcd_put_dec(unsigned char ch)
{
	
	unsigned char s=0,i=0;
	s=ch;
	while (s>9)
	{ s=s-10; i++; }    	
	
if (i>0){lcd_putc('0'+i);}   lcd_putc('0'+s);
	
}

void lcd_init(void)
{
	DISPDDR = 0xff;
	DISPPORT = 0;
	_delay_ms(50);

	lcd_write( _BV(LCD_DB5) | _BV(LCD_DB4) );
	_delay_ms(5);
	lcd_write( _BV(LCD_DB5) | _BV(LCD_DB4) );
	_delay_ms(1);
	lcd_write( _BV(LCD_DB5) | _BV(LCD_DB4) );
	_delay_ms(2);

	lcd_write( _BV(LCD_DB5) );
	_delay_ms(2);

	lcd_write( _BV(LCD_DB5) );
	_delay_ms(2);
	lcd_write( _BV(LCD_DB7) | _BV(LCD_DB6) );
	_delay_ms(2);

	lcd_write( 0 );
	lcd_write( _BV(LCD_DB7) );
	_delay_ms(2);

	lcd_write( 0 );
	lcd_write( _BV(LCD_DB4) );
	_delay_ms(2);

	lcd_write( 0 );
	lcd_write( _BV(LCD_DB6) | _BV(LCD_DB5) );
	_delay_ms(2);

	lcd_write( 0 );
	lcd_write( _BV(LCD_DB7) | _BV(LCD_DB6) | _BV(LCD_DB5) );
	_delay_ms(2);
}

void lcd_puts(char *str)
{
    register char c;

    while ( (c = *str++) ) {
        lcd_putc(c);
    }
}

void lcd_puts_p(char *str)   //строка?
{
    register char c;

    while ( (c = pgm_read_byte(str++)) ) {
        lcd_putc(c);
    }
}

void lcd_puts_c(const char *str)
{
	register char c;

	while ( (c = pgm_read_byte(str++)) ) {
		lcd_putc(c);
	}
}


void lcd_gotoxy(unsigned char x, unsigned char y)
{
     if (y)
        lcd_write( _BV(LCD_DB7) | _BV(LCD_DB6) );
     else
        lcd_write( _BV(LCD_DB7) );

        lcd_write( 
		  ((x & _BV(3))>>3) <<	LCD_DB7
		| ((x & _BV(2))>>2) <<	LCD_DB6
		| ((x & _BV(1))>>1) <<	LCD_DB5
		| (x & 1) <<		LCD_DB4
	);
}

void lcd_clrscr(unsigned char data)
{
     unsigned char i = 0;
     if (data == 1)
     {
        lcd_gotoxy(0, 0);
	for (i=0; i<16; i++)
        	lcd_putc(' ');
        lcd_gotoxy(0, 0);
     }
     
     if (data == 2)
     {
        lcd_gotoxy(0, 1);
	for (i=0; i<16; i++)
        	lcd_putc(' ');
        lcd_gotoxy(0, 1);
     }
     
     if (data == 3)
     {
        /*Clear display*/
        lcd_write( 0 );
        lcd_write( (1<<LCD_DB4) );
        //_delay_us(120);         //Delay after clearing display
     }
}

#endif
