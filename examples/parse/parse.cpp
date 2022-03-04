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

template<class T>
bool parse(const char* json, T *req)
{
    return true;
}

extern "C" void app_main() 
{    
    for (int i = 2; i >= 0; i--) {
        printf("Restarting in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    Command cmd = Command();
    while (1)
    {
        // REQUEST_BODY_BASIC reqBasic;
        // if (cmd.parseBasic("{\"id\":123,\"cmd\":\"info\"}", &reqBasic)) {
        //     RESPONSE_BODY_BASIC resBasic;
        //     resBasic.err = NULL;
        //     resBasic.id = reqBasic.id;
        //     printf(cmd.printBasic(&resBasic));
        // } else {
        //     printf("parse failed!");
        // }

        // int reqInfo = cmd.parse<int>();
        // printf("%d",reqInfo);
        
        //int x1 = 0, y1 = 1;
        // auto result1 = add(x1, y1);
        // int result = (int)result1;
        
        // REQUEST_BODY_INFO info = REQUEST_BODY_INFO();
        // if (cmd.parse<REQUEST_BODY_INFO>("Hello!", &info)) {
        //     printf("success!");
        // } else {
        //     printf("failed!");
        // }

        REQUEST_BODY_CUSTOM custom = REQUEST_BODY_CUSTOM();
        if (cmd.parseCustom("{\"id\":123,\"cmd\":\"custom\",\"data\":\"1234567890ABCDEF\"}", &custom)) {
            printf("success!");
        } else {
            printf("failed!");
        }


        vTaskDelay(1000 / portTICK_PERIOD_MS);

    }

}