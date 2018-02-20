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

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

void display(int digit)
{
	if (digit < 15)
	{
		PORTB = Numbers[digit];
	}
	else{
		PORTB = Numbers[16];
	}	
}

int main(void)
{
	
	DDRC = 0b00000000;
	DDRD = 0b00000000;
	
	DDRB = 0b11111111;
    /* Replace with your application code */
	int num = 0;
	display(num);
    while (1) 
    {
		if ((PINC & 0b0000001) && !(PIND & 0b00000001))
		{
			num++;
			display(num);
			wait(200);
		}
		if(!(PINC & 0b0000001) && (PIND & 0b00000001)){
			num--;
			display(num);
			wait(200);
		}
	 	if ((PINC & 0b0000001) && (PIND & 0b00000001))
		{
			num = 0;
			display(num);
			wait(200);
		}
	}
}

