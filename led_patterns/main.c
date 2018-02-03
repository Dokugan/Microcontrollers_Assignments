/*
 * led_patterns.c
 *
 * Created: 2-2-2018 11:14:53
 * Author : stijn
 */ 

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

void wait( int ms){
	for (int i=0; i<ms; i++)
	{
		_delay_ms(1);
	}
}

int main(void)
{
	int i;
	DDRD = 0b11111111;
	/* Replace with your application code */
	while (1)
	{		
		PORTD = 0b10000000;
		for (i = 0; i < 8; i++)
		{
			
			wait(50);
			PORTD >>= 1;
		}
	}
}

