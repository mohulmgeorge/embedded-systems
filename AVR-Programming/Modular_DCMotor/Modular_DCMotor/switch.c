#include <avr/io.h>
#include "switch.h"

static volatile uint8_t cs = 1; //current state of switch
static volatile uint8_t ps = 1; //previous state of switch
volatile uint8_t count = 0; //count switch press

void switch_init() {
	DDRD &= ~(1<<DDD1); //assign PD1 as input
	PORTD |= 1<<PORTD1; //internally pull up PD1
}

void switch_read() {
	cs = (PIND & (1<<PIND1))? 1 : 0; //read current state of switch
	
	if((ps == 1) && (cs == 0)) {
		count++;
		ps = cs; //assign current state of switch into previous state
	}
	else if((ps == 1) && (cs == 1))
	ps = cs;
	else if((ps == 0) && (cs == 0))
	ps = cs;
	else if((ps == 0) && (cs == 1))
	ps = cs;
}