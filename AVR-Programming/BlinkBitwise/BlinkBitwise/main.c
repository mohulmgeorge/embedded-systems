/*
 * BlinkBitwise.c
 *
 * Created: 2025-11-19 7:12:17 PM
 * Author : mohul
 */ 

#define F_CPU 16000000UL
#define DLY 1000

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRB |= 1<<DDB5;
    /* Replace with your application code */
    while (1) 
    {
		PORTB |= 1<<PORTB5; //set PB5
		_delay_ms(1000);
		PORTB &= ~(1<<PORTB5); //reset PB5
		_delay_ms(1000);
    }
}

