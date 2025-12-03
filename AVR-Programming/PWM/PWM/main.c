

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

void configure();

int main(void)
{
	configure();
	
    while (1) 
    {
		for(int i=0; i<256; i++) {
			OCR0A = i;
			_delay_ms(5);
		}
		for(int i=255; i>0; i--) {
			OCR0A = i;
			_delay_ms(5);
		}
    }
}

void configure() {
	//OCR0A = 0; //50% duty cycle
	DDRD |= 1<<DDD6; //assign PD6 as output
	TCCR0A |= 1<<COM0A1; //clear OC0A on up-count, set OC0A on down-count
	TCCR0A = (TCCR0A & ~(1<<WGM01)) | 1<<WGM00; //set PWM, phase correct, TOP is 0xFF
	TCCR0B = (TCCR0B & ~(1<<CS02 | 1<<CS00)) | 1<<CS01; //prescaler 8
}