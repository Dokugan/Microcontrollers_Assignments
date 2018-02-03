/*
 * led_button.c
 *
 * Created: 2-2-2018 10:55:42
 * Author : stijn
 */ 
#define BIT(x) (1 << (x))
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
	DDRC = 0x00;
	DDRD = 0b11111111;
	DDRA = 0b11111111;
	DDRB = 0b11111111;
	DDRE = 0b11111111;
	DDRF = 0b11111111;
	DDRE = 0b11111111;
	DDRF = 0b11111111;
	DDRG = 0b11111111;
	
	PORTA = 0x00;
	PORTB = 0x00;
	PORTD = 0x00;
	PORTE = 0x00;
	PORTF = 0x00;
	PORTG = 0x00;
	
	PORTD |= BIT(6);
	PORTD &= ~BIT(7);
    /* Replace with your application code */
    while (1) 
    {
		if (PINC & 0x01)
		{
			wait(500);
			PORTD ^= (BIT(7)| BIT(6));
		}
    }
}

