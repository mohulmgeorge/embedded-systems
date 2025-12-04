#ifndef DS1722_H_
#define DS1722_H_

void ds1722_init();
void ds1722_config_write(uint8_t address, uint8_t value);
uint8_t ds1722_config_read(uint8_t address);
uint16_t ds1722_temp_read(uint8_t address);


#endif /* DS1722_H_ */