//WAP to turn on an LED connected to PB5 pin when a switch connected to 
//pin PD2 is pressed. Note that Pin PD2 is normally pulled down.

#define F_CPU 16000000UL

#include <avr/io.h>

void configure();

int main(void)
{
	configure();
	
    while (1) 
    {
		if(PIND&(1<<PIND2))
			PORTB |= 1<<PORTB5;
		else
			PORTB &= ~(1<<PORTB5);
    }
}

void configure() {
	DDRB |= 1<<DDB5; //assign PB5 as output
	DDRD &= ~(1<<DDD2); //assign PD2 as input
}
