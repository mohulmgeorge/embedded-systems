#include <avr/io.h>
#include "timer.h"

void timer0_init() {
	TCCR0A |= 1<<WGM00; //PWM, phase-correct
	TCCR0A = (TCCR0A & ~(1<<COM0A0)) | 1<<COM0A1; //clear OC0A on up-count, set on down-count, when comapre match happens
}

void timer0_start() {
	TCCR0B |= 1<<CS00; //no prescaling
}

void timer0_stop() {
	TCCR0B &= ~(1<<CS02 | 1<<CS01 | 1<<CS00); //no clock source, timer stopped
}