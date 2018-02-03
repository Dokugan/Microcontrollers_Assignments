/*
 * led_lookup.c
 *
 * Created: 2-2-2018 11:36:16
 * Author : stijn
 */ 

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

void wait( int ms){
	for (int i=0; i<ms; i++)
	{
		_delay_ms(1);
	}
}

void cyclePattern(int* arr, int length, int right){
	int* tempArray = (int*) malloc(length * sizeof(int));
	int i;
	int pos = 0;
	
	if (right == 1){
		for (i = 0; i < length; i++)
		{
			if (i - 1 == -1)
			{
				pos = length - 1;				
				tempArray[i] = arr[pos];
			}else{
				tempArray[i] = arr[i - 1];
			}
		}
	}
	else
	{
		for (i = length; i > 0; i--)
		{
			if (i + 1 == length)
			{
				pos = length + 1;
				tempArray[i] = arr[pos];
				}else{
				tempArray[i] = arr[i + 1];
			}
		}
	}
	
	for (i = 0; i < length; i++){
		arr[i] = tempArray[i];	
	}
	free(tempArray);
}

int intFromBitArray(int* arr, int lenght){
	int i;
	int value = 0;
	
	for (i = lenght; i > 0; i--)
	{
		value += arr[i] * pow(2, i);
	}
	return value;
}

int main(void)
{
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xFF;
	DDRE = 0xFF;
	DDRF = 0xFF;
	DDRG = 0xFF;
	
	int pattern[7] = {0b10000001,0b01000010,0b00100100,0b00011000,0x00,0x00,0x00};
	
	while (1)
	{
		cyclePattern(pattern, 7, 1);
		PORTA = pattern[0];
		PORTB = pattern[1];
		PORTC = pattern[2];
		PORTD = pattern[3];
		PORTE = pattern[4];
		PORTF = pattern[5];
		PORTG = pattern[6];
		wait(200);
	}
}
