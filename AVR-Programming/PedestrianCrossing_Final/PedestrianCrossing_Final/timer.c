#include "timer.h"
#include "config.h"
#include "traffic.h"
#include <avr/io.h>
#include <avr/interrupt.h>

static volatile uint8_t prev_state_switch = 1; //store previous state of switch; initialize as HIGH
static volatile uint8_t count0 = 0; //count timer0 interrupt cycles
volatile uint8_t seconds = 0; //count seconds
extern volatile signal_state cs;
extern volatile signal_state ps;

void timer_init() {
	//configure timer0
	OCR0A = 155; //count ~10ms every clock cycle
	TCCR0A &= ~(1<<COM0A1 | 1<<COM0A0 | 1<<COM0B1 | 1<<COM0B0); //normal port operation; OC0A and OC0B are disconnected
	TCCR0A = (TCCR0A & ~(1<<WGM00)) | 1<<WGM01; //CTC mode; mode2
	TCCR0B &= ~(1<<WGM02); //CTC mode; mode2
	TCCR0B &= ~(1<<FOC0A | 1<<FOC0B); //normal operation mode
	TIMSK0 = (TIMSK0 & ~(1<<OCIE0B | 1<<TOIE0)) | 1<<OCIE0A; //set output compare match A interrupt enable;
	//sei(); //set global interrupt enable bit in SREG
	//TCCR0B = (TCCR0B & ~(1<<CS01)) | 1<<CS02 | 1<<CS00; //1 0 1; 1024 prescaler; clock start
	
	//configure PCINT0
	PCICR |= 1<<PCIE0; //set pin change interrupt enable 0 bit
	PCMSK0 |= 1<<PCINT0; //enable PCINT0 pin change enable mask pin
}

void timer_start() {
	TCCR0B = (TCCR0B & ~(1<<CS01)) | 1<<CS02 | 1<<CS00; //1 0 1; 1024 prescaler; clock start
}

void timer_stop() {
	TCCR0B &= ~(1<<CS01 | 1<<CS02 | 1<<CS00); //0 0 0; reset CS00, CS01, CS02; clock stop
}

//interrupt handling for TIMER0
ISR(TIMER0_COMPA_vect) {
	count0++;
	if(count0 == 100) {
		count0 = 0;
		seconds++;
	}
}

//interrupt handling for PCINT0
ISR(PCINT0_vect) {
	uint8_t curr_state_switch = (PINB & (1<<SWITCH))? 1 : 0; //store current state of switch
	
	//check if switch goes from HIGH to LOW; ignore LOW to HIGH
	if(prev_state_switch == 1 && curr_state_switch == 0) {
		if(cs == SRED) {
			count0 = 0;
			seconds = 0;
			timer_stop();
			PORTD &= ~(1<<RED); //reset red pin
			cs = MOTOR_CW;
			ps = SRED;
		}
		else if(cs == SYLW) {
			count0 = 0;
			seconds = 0;
			timer_stop();
			PORTD &= ~(1<<YLW); //reset yellow pin
			cs = MOTOR_CW;
			ps = SYLW;
		}
		else if(cs == SGRN) {
			count0 = 0;
			seconds = 0;
			timer_stop();
			PORTD &= ~(1<<GRN); //reset green pin
			cs = MOTOR_CW;
			ps = SGRN;
		}
	}
	
	prev_state_switch = curr_state_switch;
}