#include <avr/io.h>
#include "switch.h"
#include "motor.h"
#include "timer.h"

#define F_CPU 16000000UL

int main(void)
{
	switch_init();
	motor_init();
	timer0_init();
	
	
    while (1) 
    {
		switch_read();
		motor_run();	
    }
}

