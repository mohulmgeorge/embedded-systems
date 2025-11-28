//WAP to implement a traffic light. The sequence of operation of traffic light is as follows
//Red (5 sec), Yellow (3 sec), Green (5 sec), Yellow (3 sec), Red (5 sec). If a switch is
//pressed anytime, then the signal changes to Red. Then motor rotates clockwise for 5s,
//wait for 10s, motor rotates anti-clockwise for 5s.

#include "traffic.h"
#include "timer.h"
#include "motor.h"
#include "display.h"
#include <avr/interrupt.h>

int main(void)
{
	traffic_init();
	timer_init();
	motor_init();
	display_init();
	sei();  //enable global interrupt bit in SREG (status register)
	
	while (1)
	{
		traffic_update();
	}
	
	return 0;
}