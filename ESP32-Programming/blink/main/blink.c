#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LED_GPIO 2

void app_main(void)
{
    gpio_reset_pin(LED_GPIO);
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT); //setting output direction
    while (1)
    {
        gpio_set_level(LED_GPIO, 1);
        //delay
        vTaskDelay(1000/portTICK_PERIOD_MS); //delay of 1 second
        gpio_set_level(LED_GPIO, 0);
        //delay
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}
