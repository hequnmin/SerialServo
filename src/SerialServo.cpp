#include "SerialServo.hpp"

namespace ATE
{
    // SerialServo::SerialServo(/* args */)
    // {
    //     // 缓存分配内存
    //     buffer = (uint8_t *)malloc(BUFFER_SIZE);
    // }

    SerialServo::SerialServo(uart_port_t uartnum)
    {
        // 设置UART
        uartNum = uartnum;
        // 缓存分配内存
        buffer = (uint8_t *)malloc(BUFFER_SIZE);
        buffersize = 0;
    }

    SerialServo::~SerialServo()
    {
        // 释放内容
        free(buffer);
    }

    void SerialServo::onRequest(onRequestPointer pointer)
    {
        requestCallback = pointer;
        self = this;
    }

    void SerialServo::afterResponse(afterResponsePointer pointer)
    {
        responseCallback = pointer;
        self = this;
    }

    void SerialServo::begin(int baud, int8_t rxPin, int8_t txPin)
    {
        uartInit(baud, rxPin, txPin);

        // xTaskCreate(uart_task, "uart_task", 1024, NULL, 10, NULL);
    }

    void SerialServo::uartInit(int baud, int8_t rxPin, int8_t txPin) {	
        // Set HW Uart
        // uart_config_t uart_config = {
        //     .baud_rate = baud,							//波特率
        //     .data_bits = UART_DATA_8_BITS,					//数据位
        //     .parity = UART_PARITY_DISABLE,					//校验位
        //     .stop_bits = UART_STOP_BITS_1,					//停止位
        //     .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,			//流控位
        //     .rx_flow_ctrl_thresh = 10, 					    //控制模式
        // };
        uart_config_t uart_config = {
            .baud_rate = baud,							//波特率
            .data_bits = UART_DATA_8_BITS,					//数据位
            .parity = UART_PARITY_DISABLE,					//校验位
            .stop_bits = UART_STOP_BITS_1,					//停止位
            .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,			//流控位
            .source_clk = UART_SCLK_APB,
        };

        //ESP_ERROR_CHECK(uart_param_config(EX_UART_NUM, &uart_config));
        ESP_ERROR_CHECK(uart_param_config(uartNum, &uart_config));
        
        // Set UART pins	
        //ESP_ERROR_CHECK(uart_set_pin(EX_UART_NUM, txPin, rxPin, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
        ESP_ERROR_CHECK(uart_set_pin(uartNum, txPin, rxPin, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
        
        // Install UART driver using an event queue here
        //ESP_ERROR_CHECK(uart_driver_install(EX_UART_NUM, BUFFER_SIZE * 2, 0, 0, NULL, 0));
        //ESP_ERROR_CHECK(uart_driver_install(uartNum, BUFFER_SIZE * 2, 0, 0, NULL, 0));
        ESP_ERROR_CHECK(uart_driver_install(uartNum, BUFFER_SIZE * 2, BUFFER_SIZE * 2, 0, NULL, 0));
        
    }

    void SerialServo::listen() {
        // 读入uart数据
        //int len = uart_read_bytes(EX_UART_NUM, buffer, BUFFER_SIZE, 20 / portTICK_RATE_MS);

        int len = uart_read_bytes(uartNum, buffer, BUFFER_SIZE - 1, 20 / portTICK_RATE_MS);
        if (len > 0) {
            buffersize = len;
            buffer[len] = '\0';
            uart_flush(uartNum);
            if (requestCallback != NULL) {
                requestCallback();
            }
        }
    }

    void SerialServo::response(const char *json) {

        uart_write_bytes(uartNum, json, strlen(json));

        if (responseCallback != NULL) {
            vTaskDelay(10 / portTICK_RATE_MS);
            responseCallback();
        }
    }

    void SerialServo::response(unsigned char *data, int len) {
        uart_write_bytes(uartNum, data, len);
        if (responseCallback != NULL) {
            vTaskDelay(10 / portTICK_RATE_MS);
            responseCallback();
        }
    }
}
