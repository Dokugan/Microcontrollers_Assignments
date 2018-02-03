/*
 * led_blink.c
 *
 * Created: 1-2-2018 15:15:10
 * Author : stijn
 */ 
#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#define BIT(x) (1 << (x))

void wait( int ms){
	for (int i=0; i<ms; i++)
	{
		_delay_ms(1);
	}
}

int main(void)
{
	//F_CPU = 8000000;
	DDRD = 0b11111111;
	DDRA = 0b11111111;
	DDRB = 0b11111111;
	DDRC = 0b11111111;
	DDRE = 0b11111111;
	DDRF = 0b11111111;
	DDRE = 0b11111111;
	DDRF = 0b11111111;
	DDRG = 0b11111111;
	
	PORTA = 0x00;
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;
	PORTE = 0x00;
	PORTF = 0x00;
	PORTG = 0x00;
	
	PORTD |= BIT(6);
	PORTD &= ~BIT(7);
	
    while (1) 
    {			
		wait(500);
		PORTD ^= (BIT(7)| BIT(6));
    }
}

