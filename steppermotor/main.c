/*
 * steppermotor.c
 *
 * Created: 28-3-2018 13:45:31
 * Author : stijn
 */ 
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

#define BIT(x) (1 << (x))


#define SERVO_PORT PORTD
#define SERVO_DDR DDRD

#define	STEP 0
#define DIR 1
#define MS1 2
#define MS2 3
#define MS3 4

void wait( int ms){
	for (int i=0; i<ms; i++)
	{
		_delay_ms(1);
	}
}

void motorInit(){
	//set output
	DDRD = 0xFF;
	
	PORTD = 0x00;
}

void motorFullStep(int dir){
	PORTD |= (BIT(DIR) & (dir << 1));
	//MS1,2,3 > 0
	PORTD &= ~(BIT(MS1));
	PORTD &= ~(BIT(MS2));
	PORTD &= ~(BIT(MS3));
	
	PORTD |= (BIT(STEP));
	wait(10);
	PORTD &= ~(BIT(STEP));
}

void motorHalfStep(int dir){
	PORTD |= (BIT(DIR) & (dir << 1));
	//MS1,2,3 > 0
	PORTD |= (BIT(MS1));
	PORTD &= ~(BIT(MS2));
	PORTD &= ~(BIT(MS3));
	
	PORTD |= (BIT(STEP));
	wait(10);
	PORTD &= ~(BIT(STEP));
}

void motorQuarterStep(int dir){
	PORTD |= (BIT(DIR) & (dir << 1));
	//MS1,2,3 > 0
	PORTD &= ~(BIT(MS1));
	PORTD |= (BIT(MS2));
	PORTD &= ~(BIT(MS3));
	
	PORTD |= (BIT(STEP));
	wait(10);
	PORTD &= ~(BIT(STEP));
}

void motorEightStep(int dir){
	PORTD |= (BIT(DIR) & (dir << 1));
	//MS1,2,3 > 0
	PORTD |= (BIT(MS1));
	PORTD |= (BIT(MS2));
	PORTD &= ~(BIT(MS3));
	
	PORTD |= (BIT(STEP));
	wait(10);
	PORTD &= ~(BIT(STEP));
}

void motorSixteenthStep(int dir){
	PORTD |= (BIT(DIR) & (dir << 1));
	//MS1,2,3 > 0
	PORTD |= (BIT(MS1));
	PORTD |= (BIT(MS2));
	PORTD |= (BIT(MS3));
	
	PORTD |= (BIT(STEP));
	wait(10);
	PORTD &= ~(BIT(STEP));
}

int main(void)
{
	DDRC = 0x00;
	motorInit();
	int direction = 1;
	
	for (int i = 0; i < 48; i++)
	{
		motorFullStep(direction);
		wait(50);
	}
    
	while (1) 
    {
		
		//motorQuarterStep(direction);
		//wait(1000);
		//motorEightStep(direction);
		//wait(1000);
		//motorSixteenthStep(direction);
		//wait(1000);
		//direction = 1 - direction;
		if (PINC & 0x01)
		{
			wait(500);
			for (int i = 0; i < 48; i++)
			{
				motorFullStep(direction);
				wait(50);
			}
		}
		wait(50);
    }
	
}

