
#include <avr/io.h>

#define F_CPU 16000000UL
#include <util/delay.h>

void configure();
void shiftOut(uint8_t data);
void displayNumber(uint8_t tens, uint8_t ones);

//for common cathode displays
const uint8_t seg[10] = {
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

int main(void)
{
	configure();
	uint8_t num = 0;
    while (1) 
    {
		displayNumber(num/10, num%10);
		_delay_ms(250);
		num++;
		if(num==100)
			num = 0;
    }
}

void configure() {
	/*
	PB5: SCLK
	PB4: SDO
	PB3: SDI
	PB2: LOAD
	*/
	DDRB |= 1<<DDD3 | 1<<DDD2 | 1<<DDD5; //assign PB3, PB2, PB5 as output

}

void shiftOut(uint8_t data)
{
	for(uint8_t i=0; i<8; i++)
	{
		// Write bit to SDI
		if(data & 0x80) PORTB |=  (1<<PORTB3);
		else            PORTB &= ~(1<<PORTB3);

		// shift clock pulse
		PORTB |=  (1<<PORTB5);
		PORTB &= ~(1<<PORTB5);

		data <<= 1;
	}
}

void displayNumber(uint8_t tens, uint8_t ones)
{
	PORTB &= ~(1<<PORTB2);      // latch low

	shiftOut(seg[tens]);      
	shiftOut(seg[ones]);      

	PORTB |=  (1<<PORTB2);      // latch high (update)
}