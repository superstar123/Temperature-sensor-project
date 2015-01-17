
#ifndef	_LCD_H_
#define	_LCD_H_		1


#include<avr/io.h>
#include<util/delay.h>
#include<stdlib.h>



/*This macro or preprocessor defines the PORT Register to which the data pins of alphanumeric LCD are connected.*/

#ifndef LCD_DATA_PORT
#warning "LCD_DATA_PORT is not defined for lcd.h.Default PORT Register is PORTA."
#define LCD_DATA_PORT	PORTA	 
#endif



/*This macro or preprocessor defines the PORT Register to which the control pins of alphanumeric LCD are connected.*/

#ifndef LCD_CONT_PORT	
#warning "LCD_CONT_PORT is not defined for lcd.h.Default PORT Register is PORTB."
#define LCD_CONT_PORT PORTB
#endif



/*This macro or preprocessor defines the microcontroller pin to which the RS pin of alphanumeric LCD is connected.*/

#ifndef LCD_RS
#warning "LCD_RS is not defined for lcd.h.Default Pin is PB0."
#define LCD_RS PB0
#endif



/*This macro or preprocessor defines the microcontroller pin to which the RW pin of alphanumeric LCD is connected.*/

#ifndef LCD_RW
#warning "LCD_RW is not defined for lcd.h.Default Pin is PB1."
#define LCD_RW PB1
#endif




/*This macro or preprocessor defines the microcontroller pin to which the EN pin of alphanumeric LCD is connected.*/

#ifndef LCD_EN
#warning "LCD_EN is not defined for lcd.h.Default Pin is PB2."
#define LCD_EN PB2
#endif



/*This function is declared to display/write a character in the alphanumeric LCD.*/

void lcd_data_write(unsigned char data);



/*This function is declared to write a command in the alphanumeric LCD.*/

void lcd_command_write(unsigned char command);



/*This function is declared to initialize the alphanumeric LCD.*/

void lcd_init();



/*This function is declared to display/write a string in the alphanumeric LCD.*/

void lcd_string_write(char *string);



/*This function is declared to display/write a number in different number system in the alphanumeric LCD.*/

void lcd_number_write(int number,unsigned char radix);




/*Function defination.*/

void lcd_data_write(unsigned char data)
{
LCD_CONT_PORT=_BV(LCD_EN)|_BV(LCD_RS);
LCD_DATA_PORT=data;
_delay_ms(1);
LCD_CONT_PORT=_BV(LCD_RS);
_delay_ms(1);
}


void lcd_command_write(unsigned char command)
{
LCD_CONT_PORT=_BV(LCD_EN);
LCD_DATA_PORT=command;
_delay_ms(1);
LCD_CONT_PORT=0x00;
_delay_ms(1);
}

void lcd_init()
{
	lcd_command_write(0x38);
	lcd_command_write(0x01);
	lcd_command_write(0x06);
	lcd_command_write(0x0e);
	
}

void lcd_string_write(char *string)
{
while (*string)
lcd_data_write(*string++);
}

void lcd_number_write(int number,unsigned char radix)
{
char *number_string="00000";
itoa(number,number_string,radix);
while (*number_string)
lcd_data_write(*number_string++);
}
#endif

