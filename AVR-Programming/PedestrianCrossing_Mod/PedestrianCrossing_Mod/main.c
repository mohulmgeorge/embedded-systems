/*
Green light by default. When user presses switch, count down timer for 10 seconds. Then signal turn yellow
for 3 seconds and then turns red. Then motor operates clockwise for 5 seconds, then a countdown timer runs
for 10 seconds, and then motor operates anti-clockwise for 5 seconds.
*/

#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL
#define SDI 5
#define SCLK 4
#define LOAD 3

typedef	enum {
	GO,
	STOP,
	COUNTDOWN,
	GATE_CLOSE,
	PEDESTRIAN_CROSS,
	GATE_OPEN
} state;

int count0 = 0; //count timer0 interrupt cycles
uint8_t prev_state_pcint0; //store previous state of pcint0 pin
state s = GO;
//for common cathode displays
const uint8_t digits[10] = {
	0b00111111, // 0
	0b00000110, // 1
	0b01011011, // 2
	0b01001111, // 3
	0b01100110, // 4
	0b01101101, // 5
	0b01111101, // 6
	0b00000111, // 7
	0b01111111, // 8
	0b01101111  // 9
};

void configure();
void stop_timer();
void start_timer();
void cw();
void ccw();
void stp();
void display_number(uint8_t digit1, uint8_t digit2);
void shift_out(uint8_t data);

int main(void)
{
	uint8_t seconds = 0;
	configure();
	prev_state_pcint0 = (PINB & (1<<PINB0))? 1 : 0;
	
    while (1) 
    {
		switch(s) {
			case GO:
				PORTD |= 1<<PORTD2; //set PD2
				display_number(seconds/10,seconds%10);
				break;
			case COUNTDOWN:
				if(count0 == 100) {
					count0 = 0;
					seconds++;
				}
				if(seconds == 15) {
					seconds = 0;
					stop_timer();
					s = STOP;
					
					start_timer();
					PORTD &= ~(1<<PORTD2); //reset PD2
					PORTD |= (1<<PORTD1); //set PD1
				}
				display_number((15-seconds)/10,(15-seconds)%10);
				break;
			case STOP:
				if(count0 == 100) {
					count0 = 0;
					seconds++;
				}
				if(seconds == 3) {
					seconds = 0;
					stop_timer();
					s = GATE_CLOSE;
					
					start_timer();
					PORTD &= ~(1<<PORTD1); //reset PD1
					PORTD |= (1<<PORTD0); //set PD0
					
				}
				display_number((3-seconds)/10,(3-seconds)%10);
				break;
			case GATE_CLOSE:
				cw();
				if(count0 == 100) {
					count0 = 0;
					seconds++;
				}
				if(seconds == 5) {
					seconds = 0;
					count0 = 0;
					stp();
					stop_timer();
					s = PEDESTRIAN_CROSS;
					start_timer();
				}
				display_number((5-seconds)/10,(5-seconds)%10);
				break;
			case PEDESTRIAN_CROSS:
				//if((count0 == 50) && (seconds >= 5)) {
					//PORTD ^= 1<<PORTD3; //toggle PD3
				//}
				if(count0 == 100) {
					count0 = 0;
					PORTD ^= 1<<PORTD3; //toggle PD3
					seconds++;
				}
				if(seconds == 10) {
					PORTD &= ~(1<<PORTD3); //reset PD3
					seconds = 0;
					stop_timer();
					s = GATE_OPEN;
					start_timer();
				}
				display_number((10-seconds)/10,(10-seconds)%10);
				break;
			case GATE_OPEN:
				ccw();
				if(count0 == 100) {
					count0 = 0;
					seconds++;
				}
				if(seconds == 5) {
					seconds = 0;
					stp();
					stop_timer();
					s = GO;
					PORTD &= ~(1<<PORTD0); //reset PD0
				}
				display_number((5-seconds)/10,(5-seconds)%10);
				break;				
			default:
				break;
		}	
    }
}

void configure() {
	DDRD |= 1<<DDD0 | 1<<DDD1 | 1<<DDD2 | 1<<DDD3; //assign PD0, PD1, PD2, PD3 as output
	DDRB = (DDRB & ~(1<<DDB0)) | 1<<DDB1 | 1<<DDB2; //assign PB0 as input and PB1, PB2 as output
	PORTD &= ~(1<<PORTD0 | 1<<PORTD1 | 1<<PORTD2 | 1<<PORTD3); //reset PD0, PD1, PD2, PD3
	PORTB = (PORTB & ~(1<<PORTB1 | 1<<PORTB2)) | 1<<PORTB0; //reset PB1, PB2; internally pull up PB0
	DDRC |= 1<<SDI | 1<<SCLK | 1<<LOAD; //assign SDI, SCLK, LOAD pins as output
	
	OCR0A = 155; //(OCR0A + 1)
	TCCR0A &= ~(1<<COM0A1 | 1<<COM0A0 | 1<<COM0B1 | 1<<COM0B0); //normal port operation; OC0A and OC0B are disconnected
	TCCR0A = (TCCR0A & ~(1<<WGM00)) | 1<<WGM01; //CTC mode; mode2
	TCCR0B &= ~(1<<WGM02); //CTC mode; mode2
	TCCR0B &= ~(1<<FOC0A | 1<<FOC0B); //normal operation mode
	TIMSK0 = (TIMSK0 & ~(1<<OCIE0B | 1<<TOIE0)) | 1<<OCIE0A; //set output compare match A interrupt enable;
	//sei(); //set global interrupt enable bit in SREG
	//TCCR0B = (TCCR0B & ~(1<<CS01)) | 1<<CS02 | 1<<CS00; //1 0 1; 1024 prescaler; clock start
	
	//EICRA &= ~(1<<ISC11 | 1<<ISC10); //00; low level of INT1 generates interrupt request; EICRA (ext interrupt control register A)
	//EIMSK |= 1<<INT1; //enable external interrupt request 1 bit in EIMSK (external interrupt mask register)
	PCICR |= 1<<PCIE0; //set pin change interrupt enable 0 bit
	PCMSK0 |= 1<<PCINT0; //enable PCINT0 pin change enable mask pin
	sei();  //enable global interrupt bit in SREG (status register)	
}

void stop_timer() {
	TCCR0B &= ~(1<<CS01 | 1<<CS02 | 1<<CS00); //0 0 0; reset CS00, CS01, CS02; clock stop
}

void start_timer() {
	TCCR0B = (TCCR0B & ~(1<<CS01)) | 1<<CS02 | 1<<CS00; //1 0 1; 1024 prescaler; clock start
}

ISR(PCINT0_vect) {
	uint8_t curr_state_pcint0 = (PINB & (1<<PINB0))? 1 : 0;
	
	if(prev_state_pcint0 == 1 && curr_state_pcint0 == 0 && s == GO) {
		stop_timer();
		s = COUNTDOWN;
		start_timer();
	}
	
	prev_state_pcint0 = curr_state_pcint0;
}

ISR(TIMER0_COMPA_vect) {
	count0++;
}

void cw() {
	PORTB |= 1<<PORTB2; //set PORTB2
	PORTB &= ~(1<<PORTB1); //reset PORTB1
}

void ccw() {
	PORTB |= 1<<PORTB1; //set PORTB1
	PORTB &= ~(1<<PORTB2); //reset PORTB2
}

void stp() {
	PORTB &= ~(1<<PORTB1); //reset PORTB1
	PORTB &= ~(1<<PORTB2); //reset PORTB2
}

void shift_out(uint8_t data)
{
	for(uint8_t i=0; i<8; i++)
	{
		//isolate MSB and write bit to SDI
		if(data & 0x80)
			PORTC |=  (1<<SDI);
		else
			PORTC &= ~(1<<SDI);

		//shift clock (SCLK) pulse
		PORTC |=  (1<<SCLK);
		PORTC &= ~(1<<SCLK);

		data <<= 1; //left shift data variable
	}
}

void display_number(uint8_t digit1, uint8_t digit2)
{
	PORTC &= ~(1<<LOAD);      //latch low

	shift_out(digits[digit1]);
	shift_out(digits[digit2]);

	PORTC |=  (1<<LOAD);      //latch high (update)
}