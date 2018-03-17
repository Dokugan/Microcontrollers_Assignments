/*
 * main.c
 *
 * Created: 1-3-2018 12:48:43
 *  Author: stijn
 */ 
#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

#include "lcd_display_functions.h"


int main(void){
	DDRD = 0xFF;
	lcd_4bit_init();
	lcd_write_command(LCDBLINK);
	lcd_write_string("hallostijhn", 11);
	
	lcd_set_cursor(5, 2);
	
	/*
	while (1)
	{
		PORTD ^= (1<<7);	// Toggle PORTD.7
		_delay_ms( 250 );
	}
	*/

	return 1;
}
