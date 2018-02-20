#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int i = 0;

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

ISR( INT0_vect )
{	
    if (i < 8)
    {
	    PORTB >>= 1;
	    i++;
    }
    else
    {
	    PORTB = 0b10000000;
	    i = 0;
    }    		
}

ISR( INT2_vect )
{
    if (i >= 0)
    {
	    PORTB <<= 1;
	    i--;
    }
    else
    {
	    PORTB = 0b00000001;
	    i = 7;
    }		
}

int main( void )
{
	// Init I/O
	DDRD = 0xF0;			// PORTD(7:4) output, PORTD(3:0) input	

	// Init Interrupt hardware
	EICRA |= 0x22;			// INT1 falling edge, INT0 rising edge
	EIMSK |= 0x05;			// Enable INT1 & INT0
	// Enable global interrupt system
	//SREG = 0x80;			// Of direct via SREG of via wrapper
	sei();	
	
	DDRB = 0b11111111;
	PORTB = 0b10000000;

	while (1)
	{							
	}

	return 1;
}