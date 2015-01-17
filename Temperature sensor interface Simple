//**************************************************************//
//Microcontroller			:ATmega32
//System Clock				:12MHz 
//Project					:LM35 Temperature Sensor Interfacing with ATmega32 and LCD Display
//Software					:Atmel studio 6.2
//LCD Data Interfacing		:8-Bit   
//**************************************************************//

#include <stdio.h>
#include <stdlib.h>
#include<avr/io.h>
#include<avr/interrupt.h>
/*Includes io.h header file where all the Input/Output Registers and its Bits are defined for all AVR microcontrollers*/

#define	F_CPU	1200000
/*Defines a macro for the delay.h header file. F_CPU is the microcontroller frequency value for the delay.h header file. Default value of F_CPU in delay.h header file is 1000000(1MHz)*/

#include<util/delay.h>
/*Includes delay.h header file which defines two functions, _delay_ms (millisecond delay) and _delay_us (microsecond delay)*/

#define		LCD_DATA_PORT		PORTB
/*Defines a macro for the lcd.h header File. LCD_DATA_PORT is the microcontroller PORT Register to which the data pins of the LCD are connected. Default PORT Register for data pins in lcd.h header file is PORTA*/

#define 	LCD_CONT_PORT		PORTD
/*Defines a macro for the lcd.h header File. LCD_CONT_PORT is the microcontroller PORT Register to which the control pins of the LCD are connected. Default PORT Register for control pins in lcd.h header file is PORTB*/

#define 	LCD_RS 		PD2
/*Defines a macro for the lcd.h header file. LCD_RS is the microcontroller Port pin to which the RS pin of the LCD is connected. Default Port pin for RS pin in lcd.h header file is PB0*/

#define 	LCD_RW 		PD3
/*Defines a macro for the lcd.h header file. LCD_RW is the microcontroller Port pin to which the RW pin of the LCD is connected. Default Port pin for RW pin in lcd.h header file is PB1*/

#define 	LCD_EN 		PD4
/*Defines a macro for the lcd.h header file. LCD_EN is the microcontroller Port pin to which the EN pin of the LCD is connected. Default Port pin for EN pin in lcd.h header file is PB2*/

#include "lcd.h"
/*Includes lcd.h header file which defines different functions for all Alphanumeric LCD(8-Bit Interfacing Method). LCD header file version is 1.1*/

#include "adc.h"
/*Includes adc.h header file which defines different functions for Analog to Digital Converter. ADC header file version is 1.1*/

uint32_t temperatureD;
void interupt_init()
{    
	// enable timer overflow interrupt for both Timer0 and Timer1
	TIMSK=(1<<TOIE0) | (1<<TOIE1);

	// set timer0 counter initial value to 0
	TCNT0=0x00;
	// start timer0 with /1024 prescaler
	TCCR0 = (1<<CS02) | (1<<CS00);
	// lets turn on 16 bit timer1 also with /1024
	TCCR1B |= (1 << CS10) | (1 << CS12);


}

// timer1 overflow
ISR(TIMER0_OVF_vect) {
		if(temperatureD>=3)
		{
			PORTD|=0b01000000;
			_delay_ms(200);
			PORTD&=~0b01000000;
			temperatureD = 0;
		}
}

/*
// timer0 overflow
ISR(TIMER0_OVF_vect) {
}
*/

int main(void)
{
	interupt_init();
	// enable interrupts
	sei();
	DDRB=0xff;
	//All the 8 pins of PortB are declared output (data pins of LCD are connected)

	DDRD=0b01011100;
	//PD2, PD3 and PD4 pins of PortD are declared output (control pins of LCD are connected)
	//PD5 pins of PortD are declared of input of button
	//PD6 alarm led
	
	
	int adc_output;
	//Variable declarations

	lcd_init();
	//LCD initialization

	adc_init();
	//ADC initialization

	lcd_string_write("PROJECT EE");
	//String display in 1st row of LCD

	lcd_command_write(0xc0);
	//Cursor moves to 2nd row 1st column of LCD

	lcd_string_write("START");
	//String display in 2nd row of LCD

	_delay_ms(1000);
	//Display stays for 1 second

	lcd_command_write(0x01);
	//Clear screen



	//uint16_t
	uint32_t temperatureResult;
	char buffer0[7];
	char buffer1[7];

	char bufferD[7];



	//Start of infinite loop
	while(1)
	{
		adc_output=read_adc_channel(0);
		//Reading temperature sensor value

		temperatureResult= 450*adc_output/1024;
		temperatureResult = abs(temperatureResult);
		//Temperature value in degree centigrade
		
		temperatureD = temperatureResult;

		//temperatureD = temperatureResult;
		itoa(temperatureResult,buffer0,10);

		
		adc_output=read_adc_channel(1);
		//Reading temperature sensor value

		temperatureResult= 450*adc_output/1024;
		temperatureResult = abs(temperatureResult);
		//Temperature value in degree centigrade

		temperatureD = temperatureD-temperatureResult;
		temperatureD = abs(temperatureD);

		//temperatureD = temperatureD - temperatureResult;
		itoa(temperatureResult,buffer1,10);

		
		//lcd_command_write(0xc0);
		lcd_command_write(0x80);
		//Cursor moves to 2nd row 1st column of LCD
		
		lcd_string_write(buffer0);
		//Temperature display in 2nd row of LCD 
		
		lcd_string_write("`C   ");
		//String display in 2nd row of LCD
		
		lcd_command_write(0x80 + 0x05);
		//Cursor moves to 2nd row 1st column of LCD
		
		lcd_string_write(buffer1);
		//Temperature display in 2nd row of LCD

		lcd_string_write("`C   ");
		//String display in 2nd row of LCD
		
		
		
		lcd_command_write(0x80+0x0A);
		itoa(temperatureD,bufferD,10);
		lcd_string_write(bufferD);
		lcd_string_write("`C   ");
		lcd_command_write(0xC0);
		lcd_string_write("-----");	
		
	}
}
//End of Program


