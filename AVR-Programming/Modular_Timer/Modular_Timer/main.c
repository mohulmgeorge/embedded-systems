#include <avr/io.h>
#include "timer.h"
#include "led.h"

#define F_CPU 16000000UL

int main(void)
{
	led_init();
    timer0_init();
    while (1) 
    {
		toggle_led();
		delay_ms(1000);
    }
}

