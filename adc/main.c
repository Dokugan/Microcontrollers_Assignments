/*
 * adc.c
 *
 * Created: 22/03/2018 15:11:30
 * Author : Stijn
 */ 
#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>	

void initAdc(){
	//REFS/ADMUX7:6 (reference voltage) = AVCC
	//ADLAR/ADMUX:5 (ADC left adjust result) = 1 
	//MUX/ADMUX4:0 (analog channel and gain selection bits) = ADC1 single ended
	ADMUX = 0b01100001;
	
	//ADEN/ADCSRA7 (ADC Enable) = 1
	//ADSC/ADCSRA6 (ADC Start conversion) = 1
	//ADFR/ADCSRA5 (ADC Free running) = 0
	//ADIF/ADCSRA4 (ADC intterupt flag) = - (not relevant)
	//ADIE/ADCSRA3 (ADC intterupt enable) = 1
	//ADPS/ADCSRA2:0 (ADC prescaler) = 64
	ADCSRA = 0b11001110;
}

ISR(ADC_vect){
	PORTB = ADCL;
	PORTA = ADCH;
}

void AdcConvert(){
	//start conversion (ADSC/ADCSRA6)
	ADCSRA |= 0b01000000;
}

int main(void)
{
	DDRF = 0x00;
	DDRA = 0xFF;
	DDRB = 0xFF;
	
	sei();
	
	initAdc();
	
	
    /* Replace with your application code */
    while (1) 
    {
		_delay_ms(10);
		AdcConvert();
    }
	
	return 1;
}

