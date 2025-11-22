//operate a DC motor

#define F_CPU 16000000UL
#define DLY5 5000
#define DLY3 3000

#include <avr/io.h>
#include "util/delay.h"

void cw();
void ccw();
void stp();

int main(void)
{
	DDRC |= 1<<DDC1 | 1; //assign DDRC1 and DDRC0 as output
	
	while (1)
	{
		cw();
		stp();
		ccw();
		stp();
	}
}

void cw() {
	PORTC |= 1<<PORTC0; //set PORTC0
	PORTC &= ~(1<<PORTC1); //reset PORTC1
	_delay_ms(DLY3);
}

void ccw() {
	PORTC |= 1<<PORTC1; //set PORTC1
	PORTC &= ~(1<<PORTC0); //reset PORTC0
	_delay_ms(DLY3);
}

void stp() {
	PORTC &= ~(1<<PORTC1); //reset PORTC1
	PORTC &= ~(1<<PORTC0); //reset PORTC0
	_delay_ms(DLY5);
}

