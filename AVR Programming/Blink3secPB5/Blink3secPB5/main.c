// HW: Blink PB5 with a delay of 3 sec

#define F_CPU 16000000UL
#define DLY 3000 

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRB = 0b00100000; //0x20; make PB5 as output
	
    while (1) 
    {
		PORTB = 0b00100000; //0x20; set PB5 pin
		_delay_ms(DLY); //delay of 3 seconds
		PORTB = 0b00000000; //0x00; reset PB5 pin
		_delay_ms(DLY); //delay of 3 seconds
    }
	
	return 0;
}

