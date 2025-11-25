#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

void configure();

int count = 0;

ISR(TIMER0_COMPA_vect) {
	count++;
}

int main(void)
{
	configure();
    while (1) 
    {
		if(count == 100) {
			count = 0;
			PORTD ^= (1<<PORTD1); //toggle PD1
		}
    }
}

void configure() {
	DDRD |= 1<<DDD1; //assign PD1 as output
	PORTD &= ~(1<<PORTD1); //reset PD1 
	
	OCR0A = 155; //(OCR0A + 1)
	TCCR0A &= ~(1<<COM0A1 | 1<<COM0A0 | 1<<COM0B1 | 1<<COM0B0); //normal port operation; OC0A and OC0B are disconnected
	TCCR0A = (TCCR0A & ~(1<<WGM00)) | 1<<WGM01; //CTC mode; mode2
	TCCR0B &= ~(1<<WGM02); //CTC mode; mode2
	TCCR0B &= ~(1<<FOC0A | 1<<FOC0B); //normal operation mode
	TIMSK0 = (TIMSK0 & ~(1<<OCIE0B | 1<<TOIE0)) | 1<<OCIE0A; //set output compare match A interrupt enable;
	sei(); //set global interrupt enable bit in SREG
	TCCR0B = (TCCR0B & ~(1<<CS01)) | 1<<CS02 | 1<<CS00; //1 0 1; 1024 prescaler; clock start	
}