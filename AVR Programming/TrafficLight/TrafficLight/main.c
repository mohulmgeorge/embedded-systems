#define F_CPU 16000000UL
#define DLY_RED 5000
#define DLY_YLW 2000
#define DLY_GRN 5000

#include <avr/io.h>
#include <util/delay.h>

void reset();
void red(); //DDRD0
void yellow(); //DDRD1
void green(); //DDRD2

int main(void)
{
	DDRD |= 1<<DDD0 | 1<<DDD1 | 1<<DDD2; //assign DDRD0, DDRD1, DDRD2 as output pin
	reset();
	
    while (1) 
    {
		red();
		green();
		yellow();
    }
	
	return 0;
}

void red() {
	PORTD |= 1<<PORTD0; //set PORTD0
	_delay_ms(DLY_RED);
	PORTD &= ~(1<<PORTD0); //reset PORTD0
}

void yellow() {
	PORTD |= 1<<PORTD1; //set PORTD1
	_delay_ms(DLY_YLW);
	PORTD &= ~(1<<PORTD1); //reset PORTD1
}

void green() {
	PORTD |= 1<<PORTD2; //set PORTD2
	_delay_ms(DLY_GRN);
	PORTD &= ~(1<<PORTD2); //reset PORTD2	
}

void reset() {
	PORTD &= ~(1<<PORTD0); //reset PORTD0
	PORTD &= ~(1<<PORTD1); //reset PORTD1
	PORTD &= ~(1<<PORTD2); //reset PORTD2
}
