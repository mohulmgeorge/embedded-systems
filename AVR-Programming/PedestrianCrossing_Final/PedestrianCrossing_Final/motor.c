#include "motor.h"
#include "config.h"
#include <avr/io.h>

void motor_init() {
	DDRB = (DDRB & ~(1<<SWITCH)) | 1<<MTR_P1 | 1<<MTR_P2; //assign switch pin as input and motor pins as output
	PORTB |= 1<<SWITCH; //internally pull up switch pin
}

void motor_cw() {
	PORTB |= 1<<MTR_P2; //set motor pin 2
	PORTB &= ~(1<<MTR_P1); //reset motor pin 1	
}

void motor_acw() {
	PORTB |= 1<<MTR_P1; //set motor pin 1
	PORTB &= ~(1<<MTR_P2); //reset motor pin 2	
}

void motor_stop() {
	PORTB &= ~(1<<MTR_P1); //reset motor pin 1
	PORTB &= ~(1<<MTR_P2); //reset motor pin 2
}