//Initialize two pins as output. one pin is on for 5 seconds while other pin is off.
//then both the pins are off for 3 seconds. then the other pin is on for 5 seconds
//while the first pin is off

#define F_CPU 16000000UL
#define DLY5 5000
#define DLY3 3000

#include <avr/io.h>
#include "util/delay.h"


int main(void)
{
	DDRD |= 3<<DDD1; //assign port D1 and D2 as output
	
    /* Replace with your application code */
    while (1) 
    {
		//using bitwise OR and bitwise AND operators
		PORTD |= 1<<PORTD2; //set PORTD2
		PORTD &= ~(1<<PORTD1); //reset PORTD1
		_delay_ms(DLY3);
		
		PORTD &= ~(1<<PORTD1); //reset PORTD1
		PORTD &= ~(1<<PORTD2); //reset PORTD2
		_delay_ms(DLY5);
		
		PORTD |= 1<<PORTD1; //set PORTD1
		PORTD &= ~(1<<PORTD2); //reset PORTD2
		_delay_ms(DLY3);
		       
    }
}

