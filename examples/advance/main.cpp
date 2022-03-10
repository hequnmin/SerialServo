#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "cJSON.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "nvs_flash.h"
#include <iostream>
using namespace std;
#include "SerialServo.hpp"
#include "Command.hpp"
using namespace ATE;


SerialServo srv = SerialServo(UART_NUM_0);

void restart() {
    printf("Restarting now.\n");

    fflush(stdout);
    esp_restart();
}

void onRequest()
{
    //srv.response("Hello World");
    // printf("Has a request, and callback success!\n");
    Command cmd;
    REQUEST_BODY_BASIC reqBasic = REQUEST_BODY_BASIC();
    // 解析json是否基本请求体
    if (cmd.parseBasic((const char*)srv.buffer, &reqBasic)) {

        if (reqBasic.key == REQUEST_KEY::REQUEST_KEY_INFO) {                    // 获取系统信息
            REQUEST_BODY_INFO reqInfo;
            if (cmd.parseInfo((const char*)srv.buffer, &reqInfo)) {

                // 获取MAC
                uint8_t mac_addr[8] = {0};
                esp_err_t ret = ESP_OK;
                ret = esp_efuse_mac_get_custom(mac_addr);
                if (ret != ESP_OK) {
                    esp_base_mac_addr_set(mac_addr);
                }

                RESPONSE_BODY_INFO resInfo;
                resInfo.err = reqInfo.err;
                resInfo.id = reqInfo.id;
                resInfo.mac = (char *)mac_addr;
                resInfo.ver = (char *)"0.0.0.123";  
                resInfo.chi = (char *)"esp32";
                resInfo.chn = 12;           // 设置通道号
                resInfo.cnn = 12;           // 设置连接号

                srv.response(cmd.printInfo(&resInfo));
            } else {
                RESPONSE_BODY_BASIC resError;
                resError.id = reqInfo.id;
                resError.err = reqInfo.err;
                srv.response(cmd.printBasic(&resError));        
            }
        } else if (reqBasic.key == REQUEST_KEY::REQUEST_KEY_RESET) {            // 复位/清零
            REQUEST_BODY_RESET reqReset;
            if (cmd.parseReset((const char*)srv.buffer, &reqReset)) {
                RESPONSE_BODY_RESET resReset;
                resReset.err = reqReset.err;
                resReset.id = reqReset.id;

                srv.afterResponse(restart);                     // 设置应答后回调重启函数
                srv.response(cmd.printReset(&resReset));

            } else {
                RESPONSE_BODY_BASIC resError;
                resError.id = reqReset.id;
                resError.err = reqReset.err;
                srv.response(cmd.printBasic(&resError)); 
            }
        } else if (reqBasic.key == REQUEST_KEY::REQUEST_KEY_CUSTOM) {
            REQUEST_BODY_CUSTOM reqCustom = REQUEST_BODY_CUSTOM();
            if (cmd.parseCustom((const char*)srv.buffer, &reqCustom)) {
                RESPONSE_BODY_CUSTOM resCustome = RESPONSE_BODY_CUSTOM();
                resCustome.err = reqCustom.err;
                resCustome.id = reqCustom.id;
                
                // unsigned char data[] = { 18, 52 };
                // resCustome.data = data;
                // resCustome.len = 1;
                resCustome.data = reqCustom.data;
                resCustome.len = reqCustom.len;
                srv.response(cmd.printCustom(&resCustome));
            } else {
                RESPONSE_BODY_BASIC resError;
                resError.id = reqCustom.id;
                resError.err = reqCustom.err;
                srv.response(cmd.printBasic(&resError)); 
            }
        } else {

        }

    } else {
        RESPONSE_BODY_BASIC resError;
        resError.id = reqBasic.id;
        resError.err = reqBasic.err;
        srv.response(cmd.printBasic(&resError));
    }
}

extern "C" void app_main() {

    // esp_chip_info_t chip_info;
    // esp_chip_info(&chip_info);
    // printf("This is %s chip with %d CPU core(s), WiFi%s%s, ",
    //         CONFIG_IDF_TARGET,
    //         chip_info.cores,
    //         (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
    //         (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    // printf("silicon revision %d, ", chip_info.revision);

    // printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
    //         (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    // printf("Minimum free heap size: %d bytes\n", esp_get_minimum_free_heap_size());

    // for (int i = 2; i >= 0; i--) {
    //     printf("Restarting in %d seconds...\n", i);
    //     vTaskDelay(1000 / portTICK_PERIOD_MS);
    // }

    // printf("Welcome to SerialServo!\n");
    // fflush(stdout);

    // 初始化NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    srv.begin(115200, 5, 18);
    srv.onRequest(onRequest);

    while (1)
    {
        srv.listen();
        vTaskDelay(20 / portTICK_PERIOD_MS);
        
    }
    
}




