/*
 * SPI_BMP280.c
 *
 * Created: 01-11-2025 20:15:25
 * Author : sreej
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main ()
{
	uint16_t dummy, chip_id;
	
	// Set MOSI, SCK, and SS as output
	DDRB |= (1 << DDB3) | (1 << DDB5) | (1 << DDB2) |(1 << DDB0);
	// Set MISO as input
	DDRB &= ~ (1 << DDB4);
	// Enable SPI and Master mode. Set clock rate fosc / 16
	SPCR|= (1 << SPE) | (1 << MSTR) | (1 << SPR0);
	//Select SPI mode to MODE 0.
	SPCR &= ~ ((1 << CPOL) | (1 << CPHA));
	// Pull SS low to select slave
	_delay_ms(500);
	PORTB &= ~ (1 << PB2);
	// For read operation, MSB=1, hence OR register address with 0X80
	SPDR = 0XD0 | 0X80;
	// Wait until transmission is complete
	while (! (SPSR & (1 << SPIF)));
	//To reset SPIF bit, read the SPDR data (copy data to a variable)
	dummy = SPDR; //Here we get random value stored in slave [  Equivalent expression without using dummy:(void)SPDR]
	// Pull SS high to deselect slave
	PORTB |= (1 << PB2);
	_delay_ms(500);
	// Pull SS low to select slave
	PORTB &= ~ (1 << PB2);
	//For reading the chip id, send 0X00 so that data from slave comes to master.
	SPDR = 0X00;

	// Wait until transmission is complete
	while (! (SPSR & (1 << SPIF)));
	// Read chip id which is now in SPDR
	chip_id = SPDR; // Here the original data (CHIP ID) is obtained
	_delay_ms(500);
	if (chip_id == 0x58)
	{
		// Turn LED ON
		PORTB |= (1 << PB0);
	}
	else
	{
		// Turn LED OFF
		PORTB &= ~ (1 << PB0);
	}
	// Pull SS high to deselect slave
	PORTB |= (1 << PB2);
}