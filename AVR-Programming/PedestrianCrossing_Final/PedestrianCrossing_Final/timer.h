#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>

//extern volatile uint8_t count0;
extern volatile uint8_t seconds;

void timer_init();
void timer_start();
void timer_stop();

#endif /* TIMER_H_ */