/*
 * spi.c
 *
 * Created: 22/03/2018 17:11:14
 * Author : Stijn
 */ 
#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

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

void displayDriverInit()
{
	spiss(SPI_SS);				// Select display chip (MAX7219)
	SPIsendDataMaster(0x09);      			// Register 09: Decode Mode
	SPIsendDataMaster(0xFF);				// 	-> 1's = BCD mode for all digits
	spisd(SPI_SS);			// Deselect display chip

	spiss(SPI_SS);				// Select dispaly chip
	SPIsendDataMaster(0x0A);      			// Register 0A: Intensity
	SPIsendDataMaster(0x0F);    			//  -> Level 4 (in range [1..F])
	spisd(SPI_SS);			// Deselect display chip

	spiss(SPI_SS);				// Select display chip
	SPIsendDataMaster(0x0B);  				// Register 0B: Scan-limit
	SPIsendDataMaster(0x03);   				// 	-> 1 = Display digits 0..3
	spisd(SPI_SS);			// Deselect display chip

	spiss(SPI_SS);				// Select display chip
	SPIsendDataMaster(0x0C); 				// Register 0B: Shutdown register
	SPIsendDataMaster(0x01); 				// 	-> 1 = Normal operation
	spisd(SPI_SS);			// Deselect display chip
}

// Set display on ('normal operation')
void displayOn()
{
	spiss(SPI_SS);				// Select display chip
	SPIsendDataMaster(0x0C); 				// Register 0B: Shutdown register
	SPIsendDataMaster(0x01); 				// 	-> 1 = Normal operation
	spisd(SPI_SS);			// Deselect display chip
}

// Set display off ('shut down')
void displayOff()
{
	spiss(SPI_SS);				// Select display chip
	SPIsendDataMaster(0x0C); 				// Register 0B: Shutdown register
	SPIsendDataMaster(0x00); 				// 	-> 1 = Normal operation
	spisd(SPI_SS);			// Deselect display chip
}

int main(void)
{
	DDRB = 0x01;
	SPIinitMaster();
	displayDriverInit();
	
	for (char i =1; i<=4; i++)
	{
		spiss(SPI_SS); 		// Select display chip
		SPIsendDataMaster(i);  				// 	digit adress: (digit place)
		SPIsendDataMaster(i);				// 	digit value: 0
		spisd(SPI_SS);		// Deselect display chip
	}
    wait(1000);
	
	return(1);
}

