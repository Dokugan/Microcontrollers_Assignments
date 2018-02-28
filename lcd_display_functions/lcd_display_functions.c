/*
 * lcd_display_functions.c
 *
 * Created: 22-2-2018 16:44:50
 * Author : stijn
 */ 

#include <avr/io.h>
#include <util/delay.h>

#include "lcd_display_functions.h"

void lcd_pulse_e()
{
	PORTC |= 0b1000;
	_delay_ms(1);
	PORTC &= 0b0000;
}

void lcd_4bit_init()
{	
	DDRC = 0xFF;
	PORTC = 0x00;
	
	//step 1 set 4 bit mode
	PORTC |= (LCD4BIT & 0xF0);
	lcd_pulse_e();
	
	//step 2, 2 line mode
	PORTC |= (LCD2LINE & 0xF0) //First part (0010 1000 -> 0010 0000)
	lcd_pulse_e();
	PORTC |= (LCD2LINE << 4) //Second part (0010 1000 -> 1000 0000)
	lcd_pulse_e();
	
	//step 3 turn on LCD and cursor
	PORTC |= (LCDCURSOR & 0xF0) //First part
	lcd_pulse_e();
	PORTC |= (LCDCURSOR << 4) //Second part
	lcd_pulse_e();
	
	//step 4, make cursor shift when written
	PORTC |= (LCDSHIFT & 0xF0) //First part
	lcd_pulse_e();
	PORTC |= (LCDSHIFT << 4) //Second part
	lcd_pulse_e();		
}

