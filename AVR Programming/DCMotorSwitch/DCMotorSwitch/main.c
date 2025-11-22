//WAP to rotate a DC motor clockwise when one switch is pressed, and anticlockwise when 
//another switch is pressed. The motor should remain stationary when neither of the 
//switches is pressed.

#define F_CPU 16000000UL

#include <avr/io.h>

void configure();
void cw();
void acw();
void reset();

int main(void)
{
	configure();
	reset();
	
	while (1)
	{
		if(PIND&(1<<PIND2)) //if PD2 is pressed
			cw();
		else if(PIND&(1<<PIND1)) //if PD1 is pressed
			acw();
		else //if neither PD1 nor PD2 is pressed
			reset();
		
	}
}

void configure() {
	DDRC |= 1<<DDC0; //assign PC0 as output
	DDRC |= 1<<DDC1; //assign PC1 as output
	DDRD &= ~(1<<DDD2); //assign PD2 as input
	DDRD &= ~(1<<DDD1); //assign PD1 as input
}

void cw() {
	PORTC |= 1<<PORTC0; //set PORTC0
	PORTC &= ~(1<<PORTC1); //reset PORTC1	
}

void acw() {
	PORTC &= ~(1<<PORTC0); //reset PORTC0
	PORTC |= 1<<PORTC1; //set PORTC1	
}

void reset() {
	PORTC &= ~(1<<PORTC0); //reset PORTC0
	PORTC &= ~(1<<PORTC1); //reset PORTC1
}
