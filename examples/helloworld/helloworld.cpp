#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "SerialServo.hpp"
using namespace ATE;

SerialServo srv;

void onRequest() {
    
    // // 回复字符串
    // srv.response("Hello SerialServo! ");
    
    // // 回复字节数组
    // unsigned char data[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
    // int len = 10;
    // srv.response(data, len);

    // // 回复字节数组
    // char data[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    // int len = 10;
    // srv.response((unsigned char*)data, len);

    // 回复字节数组
    int len = 255;
    char *data = new char[len];
    for (int i = 0; i < len; i++)
    {
        data[i] = i + 1;
    }
    srv.response((const char*)data, len);

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