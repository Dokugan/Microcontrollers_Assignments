/*
 * states.c
 *
 * Created: 2-2-2018 13:54:28
 * Author : stijn
 */ 
//#define STATE_ON 0b1000000
#define F_CPU 8000000
#define BIT(x) (1 << (x))
#include <avr/io.h>
#include <util/delay.h>

typedef enum
{	ON = 0,
	OFF = 750
}STATES;

STATES state = OFF;

void wait( int ms){
	for (int i=0; i<ms; i++)
	{
		_delay_ms(1);
		if (PINE & 0x01)
		{
			if (state == OFF)
			{
				state = ON;
			}
			else{
				state = OFF;
			}
		}
	}
	
}

int main(void)
{
	int delay = 1000;
	
	DDRE = 0x00;
	DDRD = 0xFF;
	PORTD &= ~BIT(7);
    while (1) 
    {		
		PORTD ^= BIT(7);
		wait(delay - state);
    }
}

