#include <stdio.h>
#include "driver/uart.h"
#include "driver/gpio.h"

#include "SerialServo.hpp"
using namespace ATE;

SerialServo srv0 = SerialServo(UART_NUM_0);
SerialServo srv1 = SerialServo(UART_NUM_1);

// 接收到srv1请求
void srv1request() {
    srv0.response("Hello Srv1");
}

void srv1affterResponse() {
    vTaskDelay(1000 / portTICK_PERIOD_MS);
}

void srv0affterResponse() {
    vTaskDelay(1000 / portTICK_PERIOD_MS);
}

void srv0request() {
    srv1.response("Hello Srv0");
}

extern "C" void app_main() {

    for (int i = 10; i >= 0; i--) {
        printf("Starting in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    srv0.begin(115200, 3, 1);
    srv0.onRequest(srv0request);
    srv0.afterResponse(srv0affterResponse);

    srv1.begin(115200, 5, 18);
    srv1.onRequest(srv1request);
    srv1.afterResponse(srv1affterResponse);

    while (1)
    {
        srv0.listen();
        srv1.listen();
    }


}
