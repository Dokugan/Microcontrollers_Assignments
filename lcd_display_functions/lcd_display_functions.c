/*
 * lcd_display_functions.c
 *
 * Created: 22-2-2018 16:44:50
 * Author : stijn
 */ 

#include <avr/io.h>
#include <util/delay.h>

#include "lcd_display_functions.h"

int write = 0;

void lcd_pulse_e()
{
	if (write == 0)
	{		
		PORTC |= 0b1000;
		_delay_ms(1);
		PORTC &= 0b0000;
	}
	else
	{
		PORTC |= 0b1010;
		_delay_ms(1);
		PORTC &= 0b0010;
	}
}

void lcd_write_command(unsigned char cmd){
	PORTC |= (cmd & 0xF0) //First part
	lcd_pulse_e();
	PORTC |= (cmd << 4) //Second part
	lcd_pulse_e();
}

void lcd_4bit_init()
{	
	DDRC = 0xFF;
	PORTC = 0x00;
	
	//step 1 set 4 bit mode
	PORTC |= (LCD4BIT & 0xF0);
	lcd_pulse_e();
	
	//step 2, 2 line mode
	lcd_write_command(LCD2LINE);
	
	//step 3 turn on LCD and cursor
	lcd_write_command(LCDCURSOR);
	
	//step 4, make cursor shift when written
	lcd_write_command(LCDSHIFT);	
}

void lcd_write_char(unsigned char c)
{
	write = 1;
	PORTC |= (c & 0xF0);
	lcd_pulse_e();
	PORTC |= (c << 4);
	lcd_pulse_e();
	write = 0;
}

void lcd_write_string(char* str, int length)
{
	for (int i = 0; i < length; i++)
	{
		lcd_write_char(str[i]);
	}
}



