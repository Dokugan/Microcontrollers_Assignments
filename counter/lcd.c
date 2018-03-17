/*
 * lcd_display_functions.c
 *
 * Created: 22-2-2018 16:44:50
 * Author : stijn
 */ 
#ifndef F_CPU
#define F_CPU 8000000
#endif
#define LCDPORT PORTC

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

#include "lcd.h"

int write = 0;

/************************************************************************/
/*	This funtion sends a high signal to pin E and then sets it back to	*/
/*	low so that that data is being send.                                */
/************************************************************************/
void lcd_pulse_e()
{
	if (write == 0)
	{		
		LCDPORT |= 0b00001000;
		_delay_ms(1);
		LCDPORT &= 0b11110000;
		_delay_ms(1);
	}
	else
	{
		LCDPORT |= 0b00001100;
		_delay_ms(1);
		LCDPORT &= 0b11110100;
		_delay_ms(1);
	}
}

void lcd_write_command(unsigned char cmd){
	LCDPORT = (cmd & 0xF0); //First part
	lcd_pulse_e();
	LCDPORT = (cmd << 4); //Second part
	lcd_pulse_e();
}

void lcd_4bit_init()
{	
	DDRC = 0xFF;
	LCDPORT = 0x00;
	
	//step 1 set 4 bit mode
	LCDPORT = (LCD4BIT & 0xF0);
	lcd_pulse_e();
	
	//step 2, 2 line mode
	lcd_write_command(LCD2LINE);
	
	//step 3 turn on LCD and cursor
	lcd_write_command(LCDCURSOR);
	
	//step 4, make cursor shift when written
	lcd_write_command(LCDSHIFT);
	
	lcd_write_command(LCDCLEAR);	
}

void lcd_write_char(unsigned char c)
{
	write = 1;
	LCDPORT = (c & 0xF0);
	lcd_pulse_e();
	LCDPORT = (c << 4);
	lcd_pulse_e();
	write = 0;
}

void lcd_write_string(char* str, int len)
{
	lcd_write_command(LCDCLEAR);
	lcd_write_command(LCDRETURNHOME);
	for (int i = 0; i < len; i++)
	{
		lcd_write_char(str[i]);
	}
}

void lcd_set_cursor(int pos, int line){
	lcd_write_command(LCDRETURNHOME);
	if (line == 2)
		pos+=40;
		
	int i;
	for (i = 0; i < pos; i++)
	{
		lcd_write_command(LCDCURSOR_R);
	}
}



