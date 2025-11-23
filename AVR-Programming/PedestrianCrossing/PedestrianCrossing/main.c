//WAP to implement a traffic light. The sequence of operation of traffic light is as follows
//Red (5 sec), Yellow (2 sec), Green (5 sec), Yellow (2 sec), Red (5 sec). If a switch is 
//pressed anytime, then the signal changes to Red. Then motor rotates clockwise for 5s,
//wait for 10s, motor rotates anti-clockwise for 10s.  

#define F_CPU 16000000UL
#define DLY_RED 5000
#define DLY_YLW 2000
#define DLY_GRN 5000
#define DLY_MTR 5000
#define DLY_WAIT 10000

#include <avr/io.h>
#include <util/delay.h>

void configure();
void reset();
void red(); //DDRD0
void yellow(); //DDRD1
void green(); //DDRD2
char is_switch();
void motor();
void cw();
void acw();
void reset_motor();

char switch_pressed = 0; //switch status variable

int main(void)
{
	configure();
	reset();
	
	while (1)
	{
		red();
		if(switch_pressed == 1) {
			switch_pressed = 0;
			continue;
		}
		yellow();
		if(switch_pressed == 1) {
			switch_pressed = 0;
			continue;
		}
		green();
		if(switch_pressed == 1) {
			switch_pressed = 0;
			continue;
		}
		yellow();
		if(switch_pressed == 1) {
			switch_pressed = 0;
			continue;
		}
	}
	
	return 0;
}

void red() {
	PORTD |= 1<<PORTD0; //set PORTD0
	_delay_ms(DLY_RED);
	PORTD &= ~(1<<PORTD0); //reset PORTD0
	if(is_switch())
		motor();
}

void yellow() {
	PORTD |= 1<<PORTD1; //set PORTD1
	_delay_ms(DLY_YLW);
	PORTD &= ~(1<<PORTD1); //reset PORTD1
	if(is_switch())
		motor();
}

void green() {
	PORTD |= 1<<PORTD2; //set PORTD2
	_delay_ms(DLY_GRN);
	PORTD &= ~(1<<PORTD2); //reset PORTD2
	if(is_switch())
		motor();
}

void reset() {
	PORTD &= ~(1<<PORTD0); //reset PORTD0
	PORTD &= ~(1<<PORTD1); //reset PORTD1
	PORTD &= ~(1<<PORTD2); //reset PORTD2
}

void configure() {
	DDRD |= 1<<DDD0 | 1<<DDD1 | 1<<DDD2; //assign DDRD0, DDRD1, DDRD2 as output pin
	DDRB &= ~(1<<DDB0); //assign B0 pin as input
	PORTB |= 1<<PORTB0; //internally pull up B0
	DDRB |= 1<<DDB1 | 1<<DDB2; //assign B1, B2 as output pin
}

char is_switch() {
	if(!(PINB&(1<<PINB0))) {
		switch_pressed = 1;
		return 1;
	}
	return 0;
}

void motor() {
	PORTD |= 1<<PORTD0; //set PORTD0; switch ON red light
	cw();
	reset_motor();
	_delay_ms(DLY_WAIT);
	acw();
	reset_motor();
	PORTD &= ~(1<<PORTD0); //reset PORTD0; switch OFF red light
}

void cw() {
	PORTB |= 1<<PORTB2; //set PORTB2
	PORTB &= ~(1<<PORTB1); //reset PORTB1
	_delay_ms(DLY_MTR);
}

void acw() {
	PORTB |= 1<<PORTB1; //set PORTB1
	PORTB &= ~(1<<PORTB2); //reset PORTB2
	_delay_ms(DLY_MTR);
}

void reset_motor() {
	PORTB &= ~(1<<PORTB1); //reset PORTB1
	PORTB &= ~(1<<PORTB2); //reset PORTB2
}
