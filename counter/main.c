#define BIT(x) (1 << (x))
#ifndef F_CPU
#define F_CPU 8000000
#endif

#include <avr/io.h>
#include "lcd.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>


int tenths = 0;

void wait( int ms){
	for (int i=0; i<ms; i++)
	{
		_delay_ms(1);
	}
}

ISR(TIMER2_COMP_vect){
	tenths++;
	TCNT2 = 0x00;
}

int main(void)
{
	DDRD &= ~BIT(7);
	TCCR2 = 0b00100111;
	TCNT2 = 0x00;
	OCR2 = 10;
	TIMSK |= BIT(7);
	sei();
	
	lcd_4bit_init();
	
	int numold = 0;
	while (1)
	{
		int num = TCNT2 + tenths * 10;
		char str[16];
		sprintf(str ,"%d", num);
		if (numold != num)
			lcd_write_string(str, strlen(str));
		numold = num;
		wait(1);
	}
	
	return 1;
}

