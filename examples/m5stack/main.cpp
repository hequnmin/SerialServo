#include <stdio.h>
#include <iostream>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>



extern "C" void app_main()
{
    for (int i = 2; i >= 0; i--) {
        printf("Restarting in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
