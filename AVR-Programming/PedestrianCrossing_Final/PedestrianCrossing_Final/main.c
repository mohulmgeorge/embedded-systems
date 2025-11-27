//WAP to implement a traffic light. The sequence of operation of traffic light is as follows
//Red (5 sec), Yellow (3 sec), Green (5 sec), Yellow (3 sec), Red (5 sec). If a switch is
//pressed anytime, then the signal changes to Red. Then motor rotates clockwise for 5s,
//wait for 10s, motor rotates anti-clockwise for 5s.

#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL
#define RED 0
#define YLW 1
#define GRN 2
#define SWITCH 0
#define MTR_P1 1
#define MTR_P2 2
#define DLY_RED 5
#define DLY_YLW 3
#define DLY_GRN 5
#define DLY_MTR 5
#define DLY_WAIT 10
#define SDI 5
#define SCLK 4
#define LOAD 3

typedef	enum {
	SRED,
	SYLW,
	SGRN,
	MOTOR_CW,
	PEDESTRIAN_CROSS,
	MOTOR_ACW
} signal_state;

uint8_t count0 = 0, seconds = 0; //count timer0 interrupt cycles, count seconds
uint8_t prev_state_switch = 1; //store previous state of switch; initialize as HIGH
signal_state ps = SRED, cs = SRED; //store previous and current signal state
//for seven segment common cathode display
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
void motor();
void cw();
void acw();
void reset_motor();
void stop_timer();
void start_timer();
void display_number(uint8_t digit1, uint8_t digit2);
void shift_out(uint8_t data);

int main(void)
{
	configure();
	
	while (1)
	{
		switch(cs) {
			case SRED:
			PORTD |= 1<<RED; // set red pin
			start_timer();
			if(count0 == 100) {
				count0 = 0;
				seconds++;
			}
			display_number((DLY_RED-seconds)/10,(DLY_RED-seconds)%10);
			if(seconds == DLY_RED) {
				seconds = 0;
				PORTD &= ~(1<<RED); //reset red pin
				stop_timer();
				cs = SYLW; //change current signal state to SYLW
				ps = SRED; //store previous state
			}			
			break;
			
			case SGRN:
			PORTD |= 1<<GRN; // set green pin
			start_timer();
			if(count0 == 100) {
				count0 = 0;
				seconds++;
			}
			display_number((DLY_GRN-seconds)/10,(DLY_GRN-seconds)%10);
			if(seconds == DLY_GRN) {
				seconds = 0;
				PORTD &= ~(1<<GRN); //reset green pin
				stop_timer();
				cs = SYLW; //change current signal state to SYLW
				ps = SGRN;//store previous state
			}
			break;
			
			case SYLW:
			PORTD |= 1<<YLW; // set yellow pin
			start_timer();
			if(count0 == 100) {
				count0 = 0;
				seconds++;
			}
			display_number((DLY_YLW-seconds)/10,(DLY_YLW-seconds)%10);
			if(seconds == DLY_YLW) {
				seconds = 0;
				PORTD &= ~(1<<YLW); //reset yellow pin
				stop_timer();
				if(ps == SRED)
					cs = SGRN; //change current signal state to SGRN
				else if(ps == SGRN)
					cs = SRED; //change current signal state to SRED
				ps = SYLW; //store previous state
			}			
			break;
			
			case MOTOR_CW:	
			PORTD |= 1<<RED; //set PORTD0; switch ON red light
			PORTB |= 1<<MTR_P2; //set motor pin 2
			PORTB &= ~(1<<MTR_P1); //reset motor pin 1
			start_timer();
			if(count0 == 100) {
				count0 = 0;
				seconds++;
			}
			display_number((DLY_MTR-seconds)/10,(DLY_MTR-seconds)%10);
			if(seconds == DLY_MTR) {
				seconds = 0;
				PORTD &= ~(1<<RED); //reset red pin
				PORTB &= ~(1<<MTR_P2); //reset motor pin 2
				PORTB &= ~(1<<MTR_P1); //reset motor pin 1
				stop_timer();
				cs = PEDESTRIAN_CROSS; //change current signal state
				ps = MOTOR_CW;//store previous state
			}
			break;
			
			case MOTOR_ACW:
			PORTD |= 1<<RED; //set PORTD0; switch ON red light
			PORTB |= 1<<MTR_P1; //set motor pin 1
			PORTB &= ~(1<<MTR_P2); //reset motor pin 2
			start_timer();
			if(count0 == 100) {
				count0 = 0;
				seconds++;
			}
			display_number((DLY_MTR-seconds)/10,(DLY_MTR-seconds)%10);
			if(seconds == DLY_MTR) {
				seconds = 0;
				PORTD &= ~(1<<RED); //reset red pin
				PORTB &= ~(1<<MTR_P2); //reset motor pin 2
				PORTB &= ~(1<<MTR_P1); //reset motor pin 1
				stop_timer();
				cs = RED; //change current signal state
				ps = MOTOR_ACW; //store previous state
			}
			break;
			
			case PEDESTRIAN_CROSS:
			PORTD |= 1<<RED; //set PORTD0; switch ON red light
			start_timer();
			if(count0 == 100) {
				count0 = 0;
				seconds++;
			}
			display_number((DLY_WAIT-seconds)/10,(DLY_WAIT-seconds)%10);
			if(seconds == DLY_WAIT) {
				seconds = 0;
				PORTD &= ~(1<<RED); //reset red pin
				stop_timer();
				cs = MOTOR_ACW; //change current signal state
				ps = PEDESTRIAN_CROSS; //store previous state
			}
			break;
			
			default:
			break;
		}
	}
	
	return 0;
}

void configure() {
	DDRD |= 1<<RED | 1<<YLW | 1<<GRN; //assign red, yellow, green pins as output
	DDRB = (DDRB & ~(1<<SWITCH)) | 1<<MTR_P1 | 1<<MTR_P2; //assign switch pin as input and motor pins as output
	PORTB |= 1<<SWITCH; //internally pull up switch pin
	PORTD &= ~(1<<SRED | 1<<SYLW | 1<<SGRN); //reset red, yellow, green pins
	
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
	
	sei();  //enable global interrupt bit in SREG (status register)
}

void motor() {
	cw();
	reset_motor();
	//_delay_ms(DLY_WAIT);
	acw();
	reset_motor();
	PORTD &= ~(1<<PORTD0); //reset PORTD0; switch OFF red light
}

void cw() {
	PORTB |= 1<<MTR_P2; //set motor pin 2
	PORTB &= ~(1<<MTR_P1); //reset motor pin 1
}

void acw() {
	PORTB |= 1<<PORTB1; //set PORTB1
	PORTB &= ~(1<<PORTB2); //reset PORTB2
	//_delay_ms(DLY_MTR);
}

void reset_motor() {
	PORTB &= ~(1<<PORTB1); //reset PORTB1
	PORTB &= ~(1<<PORTB2); //reset PORTB2
}

void stop_timer() {
	TCCR0B &= ~(1<<CS01 | 1<<CS02 | 1<<CS00); //0 0 0; reset CS00, CS01, CS02; clock stop
}

void start_timer() {
	TCCR0B = (TCCR0B & ~(1<<CS01)) | 1<<CS02 | 1<<CS00; //1 0 1; 1024 prescaler; clock start
}

//interrupt handling for PCINT0
ISR(PCINT0_vect) {
	uint8_t curr_state_switch = (PINB & (1<<SWITCH))? 1 : 0; //store current state of switch
	
	//check if switch goes from HIGH to LOW; ignore LOW to HIGH
	if(prev_state_switch == 1 && curr_state_switch == 0) {
		if(cs == SRED) {
			count0 = 0;
			seconds = 0;
			stop_timer();
			PORTD &= ~(1<<RED); //reset red pin
			cs = MOTOR_CW;
			ps = SRED;
		}
		else if(cs == SYLW) {
			count0 = 0;
			seconds = 0;
			stop_timer();
			PORTD &= ~(1<<YLW); //reset yellow pin
			cs = MOTOR_CW;
			ps = SYLW;
		}
		else if(cs == SGRN) {
			count0 = 0;
			seconds = 0;
			stop_timer();
			PORTD &= ~(1<<GRN); //reset green pin
			cs = MOTOR_CW;
			ps = SGRN;
		}
	}
	
	prev_state_switch = curr_state_switch;
}

//interrupt handling for TIMER0
ISR(TIMER0_COMPA_vect) {
	count0++;
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