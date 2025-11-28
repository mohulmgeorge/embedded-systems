#include <avr/io.h>

#ifndef DISPLAY_H_
#define DISPLAY_H_

void display_init();
void display_number(uint8_t digit1, uint8_t digit2);

#endif /* DISPLAY_H_ */