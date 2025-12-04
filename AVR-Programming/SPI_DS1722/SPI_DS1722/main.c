#include <avr/io.h>
#include "spi.h"
#include "ds1722.h"

int main(void)
{
	uint8_t config;
	int16_t temp, temp12, temp8, temp9, temp10, temp11;
	float temperature;
	
	ds1722_init();
	spi_init();
	ds1722_config_write(0x80, 0b11100010); //1SHOT disabled, 9-bit resolution, continuous temp conversion
	config = ds1722_config_read(0x00); //read configuration byte
    while (1) 
    {
		temp = ds1722_temp_read(0x02); //read MSB and LSB, and store it in temp
		
		switch((config>>1) & 0x7) {
			case 0:
				temp8 = temp >> 8; //downsize to 8 bits
				if(temp8 & 0x80)
					temp8 |= 0xFF00; //sign extension concept
				temperature = temp8 * 1.0f;
				break;
				
			case 1:
				temp9 = temp >> 7; //downsize to 9 bits
				if(temp9 & 0x100)
					temp9 |= 0xFE00; //sign extension concept
				temperature = temp9 * 0.5f;
				break;
				
			case 2:
				temp10 = temp >> 6; //downsize to 10 bits
				if(temp10 & 0x200)
					temp10 |= 0xFC00; //sign extension concept
				temperature = temp10 * 0.25f;
				break;
				
			case 3:
				temp11 = temp >> 5; //downsize to 11 bits
				if(temp11 & 0x400)
					temp11 |= 0xF800; //sign extension concept
				temperature = temp11 * 0.125f;
				break;
			
			default:
				temp12 = temp >> 4; //downsize to 12 bits
				if(temp12 & 0x800)  //if bit 11 is signed
					temp12 |= 0xF000; //sign extension concept
				temperature = temp12 * 0.0625f; //f is needed to convert into float multiplication
				break;
		}
		
    }
}

