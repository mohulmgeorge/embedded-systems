#include "config.h"
#include "traffic.h"
#include "timer.h"
#include "display.h"
#include "motor.h"
#include <avr/io.h>

//extern volatile uint8_t count0; //count timer0 interrupt cycles
extern volatile uint8_t seconds; //count seconds
volatile signal_state ps = SRED; //store previous signal state
volatile signal_state cs = SRED; //store current signal state

void traffic_init() {
	DDRD |= 1<<RED | 1<<YLW | 1<<GRN; //assign red, yellow, green pins as output
	PORTD &= ~(1<<SRED | 1<<SYLW | 1<<SGRN); //reset red, yellow, green pins
}

void traffic_update() {
	switch(cs) {
		case SRED:
		PORTD |= 1<<RED; // set red pin
		timer_start();

		display_number((DLY_RED-seconds)/10,(DLY_RED-seconds)%10);
		if(seconds == DLY_RED) {
			seconds = 0;
			PORTD &= ~(1<<RED); //reset red pin
			timer_stop();
			cs = SYLW; //change current signal state to SYLW
			ps = SRED; //store previous state
		}
		break;
		
		case SGRN:
		PORTD |= 1<<GRN; // set green pin
		timer_start();
		
		display_number((DLY_GRN-seconds)/10,(DLY_GRN-seconds)%10);
		if(seconds == DLY_GRN) {
			seconds = 0;
			PORTD &= ~(1<<GRN); //reset green pin
			timer_stop();
			cs = SYLW; //change current signal state to SYLW
			ps = SGRN;//store previous state
		}
		break;
		
		case SYLW:
		PORTD |= 1<<YLW; // set yellow pin
		timer_start();
		
		display_number((DLY_YLW-seconds)/10,(DLY_YLW-seconds)%10);
		if(seconds == DLY_YLW) {
			seconds = 0;
			PORTD &= ~(1<<YLW); //reset yellow pin
			timer_stop();
			if(ps == SRED)
			cs = SGRN; //change current signal state to SGRN
			else if(ps == SGRN)
			cs = SRED; //change current signal state to SRED
			ps = SYLW; //store previous state
		}
		break;
		
		case MOTOR_CW:
		PORTD |= 1<<RED; //set PORTD0; switch ON red light
		motor_cw();
		timer_start();
		
		display_number((DLY_MTR-seconds)/10,(DLY_MTR-seconds)%10);
		if(seconds == DLY_MTR) {
			seconds = 0;
			PORTD &= ~(1<<RED); //reset red pin
			motor_stop();
			timer_stop();
			cs = PEDESTRIAN_CROSS; //change current signal state
			ps = MOTOR_CW;//store previous state
		}
		break;
		
		case MOTOR_ACW:
		PORTD |= 1<<RED; //set PORTD0; switch ON red light
		motor_acw();
		timer_start();
		
		display_number((DLY_MTR-seconds)/10,(DLY_MTR-seconds)%10);
		if(seconds == DLY_MTR) {
			seconds = 0;
			PORTD &= ~(1<<RED); //reset red pin
			motor_stop();
			timer_stop();
			cs = RED; //change current signal state
			ps = MOTOR_ACW; //store previous state
		}
		break;
		
		case PEDESTRIAN_CROSS:
		PORTD |= 1<<RED; //set PORTD0; switch ON red light
		timer_start();
		
		display_number((DLY_WAIT-seconds)/10,(DLY_WAIT-seconds)%10);
		if(seconds == DLY_WAIT) {
			seconds = 0;
			PORTD &= ~(1<<RED); //reset red pin
			timer_stop();
			cs = MOTOR_ACW; //change current signal state
			ps = PEDESTRIAN_CROSS; //store previous state
		}
		break;
		
		default:
		break;
	}
}