//WAP to turn on an LED connected to PB5 pin when a switch connected to
//pin PD2 is pressed. Note that Pin PD2 is internally pulled up.

#define F_CPU 16000000UL

#include <avr/io.h>

void configure();

int main(void)
{
	configure();
	
	while (1)
	{
		if(!(PIND&(1<<PIND2))) //if switch is pressed, i.e., input at PD2 is zero  
		PORTB |= 1<<PORTB5; //switch ON LED
		else
		PORTB &= ~(1<<PORTB5); //switch OFF LED
	}
}

void configure() {
	DDRB |= 1<<DDB5; //assign PB5 as output
	DDRD &= ~(1<<DDD2); //assign PD2 as input
	PORTD |= (1<<PORTD2); //internally pull up PD2
}
