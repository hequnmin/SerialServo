#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "nvs_flash.h"
#include <iostream>
using namespace std;

#include "Command.hpp"
using namespace ATE;

extern "C" void app_main() 
{    
    for (int i = 2; i >= 0; i--) {
        printf("Restarting in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    Command cmd;
    while (1)
    {

        REQUEST_BODY_BASIC reqBasic;
        if (cmd.parseBasic("{\"id\":123,\"cmd\":\"info\"}", &reqBasic)) {
            RESPONSE_BODY_BASIC resBasic;
            resBasic.err = NULL;
            resBasic.id = reqBasic.id;
            printf(cmd.printBasic(&resBasic));
        } else {
            printf("parse failed!");
        }

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

}