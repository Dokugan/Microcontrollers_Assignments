/*
 * lcd_display_functions.c
 *
 * Created: 22-2-2018 16:44:50
 * Author : stijn
 */ 

#include <avr/io.h>

void lcd_4bit_init(){
	
	//step 2 set 4 bit mode
	DDRC = 0xFF;
	
	
}

