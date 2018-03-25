/*
 * timer.c
 *
 * Created: 17/03/2018 16:27:39
 * Author : Stijn
 */ 
#define BIT(x) (1 << (x))

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>	

int milis = 0;

void wait( int ms){
	for (int i=0; i<ms; i++)
	{
		_delay_ms(1);
	}
}

ISR(TIMER2_COMP_vect){
	milis++;
	if (milis == 15)
	{
		PORTD &= ~BIT(7);	
	}
	if (milis == 40)
	{
		PORTD |= BIT(7);
		milis = 0;
	}
	TCNT2 = 0;
}

int main(void)
{	
	TCCR2 = 0b00001101;
	DDRD = 0xFF;
	PORTD |= BIT(7);
	OCR2 = 8; // Compare value of counter 2
	TIMSK |= BIT(7); // T2 compare match interrupt enable
	sei();

    while (1) 
    {
		wait(1);
    }
}

