#ifndef SERIALSERVO_h
#define SERIALSERVO_h

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "cJSON.h"
#include <cstring>

//#define EX_UART_NUM UART_NUM_1
#define BUFFER_SIZE (1024)

namespace ATE
{
    enum SRV_UART_NUM { SRV_UART_NUM_0, SRV_UART_NUM_1, SRV_UART_NUM_2 };

    class SerialServo;
    typedef void (*onRequestPointer) ();
    typedef void (*afterResponsePointer) ();

    class SerialServo
    {
    private:
        onRequestPointer requestCallback;
        afterResponsePointer responseCallback;

        SerialServo *self;

        void uartInit(int baud, int8_t rxPin, int8_t txPin);

    public:
        SerialServo(/* args */);
        ~SerialServo();

        uint8_t *buffer;

        SRV_UART_NUM uartNum = SRV_UART_NUM_1;

        // 串口设置
        void begin(int baud = 115200, int8_t rxPin = 5, int8_t txPin = 18);

        // 串口接收数据后回调函数
        void onRequest(onRequestPointer pointer);

        // 串口发送数据后回调函数
        void afterResponse(afterResponsePointer pointer);

        void listen();

        void response(const char *json);

    };

}
#endif