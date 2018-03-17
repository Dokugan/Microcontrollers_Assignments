/*
 * lcd_display_functions.h
 *
 * Created: 28/02/2018 21:26:04
 *  Author: Stijn
 */ 


#ifndef LCD_H_
#define LCD_H_

									//7654 3210
									//||||-||||
#define LCD4BIT			0x20		//0010 0000
#define LCD2LINE		0x28		//0010 1000
#define LCDDISON		0x0C		//0000 1100
#define LCDCURSOR		0x0E		//0000 1110
#define LCDBLINK		0x0F		//0000 1111
#define LCDSHIFT		0x06		//0000 0110
#define LCDRETURNHOME	0x02		//0000 0010
#define LCDCURSOR_R		0x14		//0001 0100
#define LCDCURSOR_L		0x10		//0001 0000
#define LCDCLEAR		0x01		//0000 0001

void lcd_4bit_init();
void lcd_write_command(unsigned char);
void lcd_write_char(unsigned char);
void lcd_write_string(char*, int);
void lcd_set_cursor(int pos, int line);


#endif /* LCD_DISPLAY_FUNCTIONS_H_ */