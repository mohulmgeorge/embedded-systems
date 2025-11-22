/*
 * Blink.c
 *
 * Created: 2025-11-18 9:56:15 PM
 * Author : mohul
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	
	DDRD = 0b00000100; //0x04; set pin 2 of port D as output
	
    /* Replace with your application code */
    while (1) 
    {
		PORTD = 0b00000100;
		_delay_ms(1000);
		PORTD = 0b00000000;
		_delay_ms(1000);
    }
	
	return 0;
}
