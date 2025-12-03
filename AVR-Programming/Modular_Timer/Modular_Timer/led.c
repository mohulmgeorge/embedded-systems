#include <avr/io.h>
#include "led.h"

void led_init() {
	DDRD |= 1<<DDD0; //assign PD0 as output
	
}

void toggle_led() {
	PORTD ^= 1<<PORTD0; //toggle PD0
}