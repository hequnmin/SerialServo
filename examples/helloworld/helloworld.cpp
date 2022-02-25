#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "SerialServo.hpp"
using namespace ATE;

SerialServo srv;

void onRequest() {
    srv.response("Hello SerialServo! ");
}

extern "C" void app_main() {

    for (int i = 2; i >= 0; i--) {
        printf("Restarting in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    printf("Hello World!");

    fflush(stdout);

    // SerialServo初始化设置
    srv.uartNum = UART_NUM_0;   //指定UartNum，默认SRV_UART_NUM_1
    srv.begin(115200, 5, 18);       //指定 RX = 5; TX = 18;
    srv.onRequest(onRequest);       //设置接收到请求后回调函数

    while (1)
    {
        // 串口监听
        srv.listen();
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }

}