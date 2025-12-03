#include <avr/io.h>
#include "led.h"

void timer0_init() {
	OCR0A = 249; // for 1ms
	TCCR0A = (TCCR0A & ~(1<<WGM00)) | 1<<WGM01; //CTC mode
	
	TCCR0B = (TCCR0B & ~(1<<CS02)) | 1<<CS01 | 1<<CS00; //prescaler 64
	
}

void delay_ms(uint16_t ms) {
	while (ms--) {
		while(!(TIFR0&(1<<OCF0A))); //wait until OCF0A is set
		TIFR0 |= (1<<OCF0A); //write 1 to reset OCF0A flag
	}
}