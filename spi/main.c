/*
 * spi.c
 *
 * Created: 22/03/2018 17:11:14
 * Author : Stijn
 */ 
#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>

#define BIT(x)		( 1<<x )
#define DDR_SPI		DDRB					// spi Data direction register
#define PORT_SPI	PORTB					// spi Output register
#define SPI_SCK		1						// PB1: spi Pin System Clock
#define SPI_MOSI	2						// PB2: spi Pin MOSI
#define SPI_MISO	3						// PB3: spi Pin MISO
#define SPI_SS		0						// PB0: spi Pin Slave Select

void wait(int ms)
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms(1);
	}
}

void SPIinitMaster()
{
	DDR_SPI = 0xff;							// All pins output: MOSI, SCK, SS, SS_display as output
	DDR_SPI &= ~BIT(SPI_MISO);				// 	except: MISO input
	PORT_SPI |= BIT(SPI_SS);				// SS_ADC == 1: deselect slave
	
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1);
	
}

void SPIsendDataMaster(char data)
{
	SPDR = data;
	while (!(SPSR & (1 << SPIF)))
		;
}

void spiss(char slavenr)
{
	PORTB &= ~BIT(slavenr);
}

void spisd(char slavenr)
{
	PORTB |= BIT(slavenr);
}

void spiSendCommand(char adress, char value){
	spiss(SPI_SS);
	SPIsendDataMaster(adress);
	SPIsendDataMaster(value);
	spisd(SPI_SS);
}

void spiWriteNumber(int number){
	char snum[4];
	itoa(number, snum, 10);
	if (strlen(snum) <= 4)
	{
		for(int i = 1; i <= strlen(snum); i++)
		{
			spiSendCommand(i, snum[strlen(snum) - i]);
		}
	}
	else
	{
		for (char i =1; i<=4; i++)
		{
			spiSendCommand(i, 9);
		}
	}
}

void displayDriverInit()
{
	spiSendCommand(9,0xFF);	// Register 09: Decode Mode -> 1's = BCD mode for all digits

	spiSendCommand(0x0A, 0x0F);	// Register 0A: Intensity -> Level 4 (in range [1..F])
	
	spiSendCommand(0x0B, 0x03);	// Register 0B: Scan-limit -> 1 = Display digits 0..3
	
	spiSendCommand(0x0C, 0x01);	// Register 0B: Shutdown register -> 1 = Normal operation
}

// Set display on ('normal operation')
void displayOn()
{
	spiSendCommand(0x0C, 1);	// Register 0B: Shutdown register -> 1 = Normal operation
}

// Set display off ('shut down')
void displayOff()
{
	spiSendCommand(0x0C, 0);	// Register 0B: Shutdown register -> 1 = Normal operation
}

int main(void)
{
	DDRB = 0x01;
	SPIinitMaster();
	displayDriverInit();
	
	for (char i =1; i<=4; i++)
	{
		spiSendCommand(i, 0);
	}
    wait(1000);
	spiWriteNumber(12542);
	wait(1000);
	return(1);
}

