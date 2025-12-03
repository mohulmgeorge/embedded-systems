#include <avr/io.h>
#include "motor.h"
#include "timer.h"

extern volatile uint8_t count;

void motor_init() {
	DDRC |= 1<<DDC1; //assign PC1 as output
	DDRD |= 1<<DDD6; //assign PD6 (OC0A pin) as output
}

void motor_start(uint8_t n) {
	if(n == 25)
		OCR0A = 63;
	else if(n == 50)
		OCR0A = 127;
	else if(n == 75)
		OCR0A = 191;
	else if(n == 100)
		OCR0A = 254;

	PORTC &= ~(1<<PORTC1); //reset PC1
	timer0_start();
}

void motor_stop() {
	PORTC &= ~(1<<PORTC1); //reset PC1
	PORTD &= ~(1<<PORTD6); //reset PD6
	timer0_stop();
}

void motor_run() {
	if(count > 4)
		count = 0;
	
	switch (count)
	{
		case 0:
			motor_stop();
			break;
		case 1:
			motor_start(25);
			break;
		case 2:
			motor_start(50);
			break;
		case 3:
			motor_start(75);
			break;
		case 4:
			motor_start(100);
			break;
		default:
			motor_stop();
			break;
	}
}