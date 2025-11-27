
#include <avr/io.h>

#define F_CPU 16000000UL

void configure();
void delay_1s();

int main(void)
{
	configure();
    while (1) 
    {
		PORTB ^= 1<<PORTB1; //toggle PB1
		delay_1s();
    }
}

void configure() {
	DDRB |= 1<<DDD1; //assign PB1 as output
	TCNT0 = 0; //set BOTTOM value
	OCR0A = 199; //set compare register value
	//TCCR0A &= ~(1<<WGM00 | 1<<WGM01); //normal mode
	TCCR0A = (TCCR0B & ~(1<<WGM00)) | 1<<WGM01; //CTC mode
	TCCR0B = (TCCR0B & ~(1<<CS01)) | 1<<CS02 | 1<<CS00; //prescaler 1024
}

void delay_1s() {
	//for(uint8_t i=0; i<61; i++) {
		//while(!(TIFR0 & (1<<TOV0))); // wait till TOV0 is set
		//TIFR0 |= 1<<TOV0; //write 1 into TOV0 to reset TOV0
	//}
	for(uint8_t i=0; i<78; i++) {
		while(!(TIFR0 & (1<<OCR0A))); // wait till OCR0A is set
		TIFR0 |= 1<<OCR0A; //write 1 into OCR0A to reset OCR0A
	}
}