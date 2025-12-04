#include <avr/io.h>
#include "ds1722.h"
#include "config.h"

void ds1722_init() {
	DDRB = (DDRB & ~(1<<SDO)) | 1<<SCLK | 1<<SDI | 1<<CE; //assign SDO pin as input, and SDI, SCLK, CE pins as output
	
}

static void write_byte(uint8_t address, uint8_t data) {
	PORTB |= 1<<CE; //set CE pin
	
	SPDR = address; //place address in SPDR, clears SPIF flag if set 
	while(!(SPSR & (1<<SPIF))); //wait until SPIF is set
	
	SPDR = data; //place data in SPDR, clears SPIF flag
	while(!(SPSR & (1<<SPIF))); //wait until SPIF is set
	
	PORTB &= ~(1<<CE); //reset CE pin
}

static uint16_t read_byte(uint8_t address) {
	uint8_t data;
	
	PORTB |= 1<<CE; //set CE pin
	
	SPDR = address; //place address in SPDR, clears SPIF flag if set
	while(!(SPSR & (1<<SPIF))); //wait until SPIF is set
	//dummy = SPDR; //read garbage value, clears SPIF flag
	(void) SPDR; //reads and discards SPDR value, clears SPIF flag; avoids warning of 'dummy variabe set but not used'
	
	SPDR = 0xFF; //or 0x00; send dummy value to read real data
	while(!(SPSR & (1<<SPIF))); //wait until SPIF is set
	data = SPDR; //place SPDR content in data variable, clears SPIF flag
	
	PORTB &= ~(1<<CE); //reset CE pin
	
	return data;
}

static uint16_t read_bytes(uint8_t address) {
	uint8_t msb, lsb;
	
	PORTB |= 1<<CE; //set CE pin
	
	SPDR = address; //place address in SPDR, clears SPIF flag if set
	while(!(SPSR & (1<<SPIF))); //wait until SPIF is set
	//dummy = SPDR; //read garbage value, clears SPIF flag
	(void) SPDR; //reads and discards SPDR value, clears SPIF flag; avoids warning of 'dummy variabe set but not used'
	
	SPDR = 0xFF; //or 0x00; send dummy value to read real data
	while(!(SPSR & (1<<SPIF))); //wait until SPIF is set
	msb = SPDR; //place SPDR content in data variable, clears SPIF flag, read MSB
	
	SPDR = 0xFF; //or 0x00; send dummy value to read real data
	while(!(SPSR & (1<<SPIF))); //wait until SPIF is set
	lsb = SPDR; //place SPDR content in data variable, clears SPIF flag, read LSB
	
	PORTB &= ~(1<<CE); //reset CE pin
	
	return ((uint16_t) msb << 8) | lsb;
}

void ds1722_config_write(uint8_t address, uint8_t value) {
	write_byte(address, value);
}

uint16_t ds1722_temp_read(uint8_t address) {
	return read_bytes(address);
}

uint8_t ds1722_config_read(uint8_t address) {
	return read_byte(address);
}