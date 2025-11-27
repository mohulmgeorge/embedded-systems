
#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL

void stop_timer1();
void stop_timer1();
void configure();
uint16_t read_timer1();

int main(void)
{
	configure();
    while (1) 
    {
		
    }
}

void configure() {
	DDRD |= 1<<DDD1; //assign PD1 as output
	PORTD |= 1<<PORTD1; //set PD1
	OCR1A = 15624;
	//CTC mode
	TCCR1A = (TCCR1A & ~(1<<WGM11 | 1<<WGM10));
	
	//prescaler 1024; CTC mode
	TCCR1B = (TCCR1B & ~(1<<WGM13 | 1<<CS11)) | 1<<WGM12 | 1<<CS12 | 1<<CS10;
	
	//set output compare A match interrupt enable bit
	TIMSK1 |= 1<<OCIE1A;
	
	sei(); //globally enable interrupts
}

void start_timer1() {
	PRR &= ~(1<<PRTIM1); //reset PRTIM1
}

void stop_timer1() {
	PRR |= 1<<PRTIM1; //set PRTIM1
}

/*
Atomic read: How it works
When you read TCNT1L, the hardware locks (latches) the high byte (TCNT1H) internally.
Then your next read of TCNT1H returns the latched (frozen) value, not the live changing timer.
This guarantees both bytes come from the same timer tick.
Reading order is low byte first and high byte second.
*/
uint16_t read_timer1() {
	uint8_t sreg;
	uint16_t i;
	
	sreg = SREG; //store current state of global interrupt
	cli(); // disable all interrupts
	
	//read low byte first and then high byte; reading order is important
	i = TCNT1L; //read low byte
	i |= (uint16_t)TCNT1H<<8; //read high byte
	
	SREG = sreg; //restore interrupt state
	return i;
}

/*
Atomic write
Writing order is high byte first and low byte second
*/
void write_timer1(uint16_t i) {
	uint8_t sreg;
	
	sreg = SREG; //store current state of global interrupt
	cli(); // disable all interrupts
	
	//write high byte first and then low byte; writing order is important
	TCNT1H = i>>8; //write high byte
	TCNT1L = i & 0xFF; //write low byte
	
	SREG = sreg; //restore interrupt state
}

ISR(TIMER1_COMPA_vect) {
	PORTD ^= 1<<PORTD1; //toggle PD1
}