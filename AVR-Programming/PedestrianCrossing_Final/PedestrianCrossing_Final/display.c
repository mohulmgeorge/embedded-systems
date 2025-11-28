#include "display.h"
#include "config.h"
#include <avr/io.h>


//for seven segment common cathode display
static const uint8_t digits[10] = {
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

static void shift_out(uint8_t data)
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

void display_init() {
	DDRC |= (1<<SDI)|(1<<SCLK)|(1<<LOAD); //assign SDI, SCLK, LOAD pins as output
}

void display_number(uint8_t digit1, uint8_t digit2)
{
	PORTC &= ~(1<<LOAD);      //latch low

	shift_out(digits[digit1]);
	shift_out(digits[digit2]);

	PORTC |=  (1<<LOAD);      //latch high (update)
}