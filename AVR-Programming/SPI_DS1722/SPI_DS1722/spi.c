#include <avr/io.h>
#include "spi.h"

void spi_init() {
	SPCR = (SPCR & ~(1<<CPOL)) | 1<<CPHA; //CPHA must be 1, CPOL = 0: SCLK idle state is zero
	SPCR |= 1<<MSTR; //Master mode
	SPCR &= ~(1<<DORD); //MSB transmitted first 
	SPCR &= ~(1<<SPR1 | 1<<SPR0); // fOSC/4 SCK freq, max SCLK frequency of ds1722 is 5Mhz
	SPCR |= 1<<SPE; //enable SPI
	
}