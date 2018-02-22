/*
 * segment_display.c
 *
 * Created: 20-2-2018 16:28:56
 * Author : stijn
 */ 

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

const unsigned char
Numbers [17] =
{
	// Pgfe dcba
	0b00111111, // 0
	0b00000110, // 1
	0b01011011, // 2
	0b01001111, // 3
	0b01100110, // 4
	0b01101101, // 5
	0b01111101, // 6
	0b00000111, // 7
	0b01111111, // 8
	0b01101111, // 9
	0b01110111, // A
	0b01111100, // B
	0b00111001, // C
	0b01011110, // D
	0b01111011, // E
	0b01110001, // F
	0b01111001 // Error
};

const unsigned char
Animation1 [13] =
{
	// Pgfe dcba
	0b01000000, // 0
	0b00100000, // 1
	0b00010000, // 3
	0b00001000, // 4
	0b00000100, // 5
	0b00000010, // 6
	0b00000001, // 7
	0b00000010, // 8
	0b00000100, // 9
	0b00001000, // A
	0b00010000, // B
	0b00100000, // C
	0b01000000, // D
};

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

void display(unsigned char digit)
{
		
}

int main(void)
{
	
	DDRC = 0b00000000;
	DDRD = 0b00000000;
	
	DDRB = 0b11111111;
    /* Replace with your application code */
	int num = 0;
	int i = 0;
	display(num);
    while (1) 
    {
		for(i = 0; i < 13){
			display(Animation1[i]);
			wait(100);
		}
	}
}

