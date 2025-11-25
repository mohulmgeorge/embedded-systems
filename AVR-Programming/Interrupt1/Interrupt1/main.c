#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define DLY 2000

void configure();
void blink_LED1();
void blink_LED2();

uint8_t flag = 0;

ISR(INT1_vect) {
	flag = 1;
}

int main(void)
{
	configure();
	
	while (1)
	{
		blink_LED1();
		if(flag) {
			flag = 0;
			blink_LED2();
		}
	}
}

void configure() {
	DDRD &= ~(1<<DDD3); //assign PD3(INT1) pin as input
	PORTD |= 1<<PORTD3; //internally pull up PD3 pin
	DDRD |= 1<<DDD1 | 1<<DDD2; //assign PD1 and PD2 pins as output
	
	EICRA &= ~(1<<ISC11 | 1<<ISC10); //00; low level of INT1 generates interrupt request; EICRA (ext interrupt control register A)
	EIMSK |= 1<<INT1; //enable external interrupt request 1 bit in EIMSK (external interrupt mask register)
	sei();  //enable global interrupt bit in SREG (status register)
}

void blink_LED1() {
	PORTD |= 1<<PORTD1; //set PD1
	_delay_ms(DLY);
	PORTD &= ~(1<<PORTD1); //reset PD1
	_delay_ms(DLY);
}

void blink_LED2() {
	PORTD |= 1<<PORTD2; //set PD2
	_delay_ms(DLY);
	PORTD &= ~(1<<PORTD2); //reset PD2
	_delay_ms(DLY);
}