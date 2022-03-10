#ifndef COMMAND_h
#define COMMAND_h

#include <stdio.h>
#include <iostream>
#include <cstring>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "cJSON.h"
#include "Util.hpp"

using namespace std;

namespace ATE
{

    class Command;

    enum COMMAND_ERROR { 
        COMMAND_ERROR_INVALID_REQUEST 
    };

    // 请求类型
    enum REQUEST_KEY {
        REQUEST_KEY_ERROR,          // 请求类型错误
        REQUEST_KEY_BASIC,          // 基本请求
        REQUEST_KEY_INFO,           // <获取系统信息>请求
        REQUEST_KEY_RESET,          // <复位/清零>请求
        REQUEST_KEY_CUSTOM          // <自定义>请求
    };

    // 基本请求结构体
    struct REQUEST_BODY_BASIC {
        int id;                     // 请求标识号
        char* cmd = NULL;     // 请求关键字
        REQUEST_KEY key;
        const char* err = NULL;     // 错误信息（多用于暂存解析JSON的错误信息）
        REQUEST_BODY_BASIC() : id(), cmd(), key(), err() {
        }
    };

    // 基本应答结构体
    struct RESPONSE_BODY_BASIC {
        int id;                     // 请求标识号          
        const char* err = NULL;     // 错误信息
    };

    // <获取系统信息>请求结构体
    struct REQUEST_BODY_INFO : public REQUEST_BODY_BASIC {
        REQUEST_BODY_INFO() {
            key = REQUEST_KEY::REQUEST_KEY_INFO;
        }
    };

    // <获取系统信息>应答结构体
    struct RESPONSE_BODY_INFO : public RESPONSE_BODY_BASIC {
        char* chi = NULL;   // 芯片信息
        char* mac = NULL;   // 物理地址
        char* ver  = NULL;   // 嵌入系统版本
        int chn;            // 通道号
        int cnn;            // 连接号
    };

    // <复位/清零>请求结构体
    struct REQUEST_BODY_RESET : public REQUEST_BODY_BASIC {
        REQUEST_BODY_RESET() {
            key = REQUEST_KEY::REQUEST_KEY_RESET;
        }
    };

    // <复位/清零>应答结构体
    struct RESPONSE_BODY_RESET : public RESPONSE_BODY_BASIC {
    };

    // <自定义>请求结构体
    struct REQUEST_BODY_CUSTOM : public REQUEST_BODY_BASIC {
        unsigned char* data = NULL;     // 字节数组地址
        int len = 0;           // 字节数组长度
        REQUEST_BODY_CUSTOM() {
            key = REQUEST_KEY::REQUEST_KEY_CUSTOM;
        }
    };

    // <自定义>应答结构体
    struct RESPONSE_BODY_CUSTOM : public RESPONSE_BODY_BASIC {
        unsigned char* data = NULL;     // 字节数组地址
        int len = 0;           // 字节数组长度
    };


    // 指令类
    class Command
    {
    private:
        /* data */
    public:
        Command(/* args */);
        ~Command();

        // 基本请求Json解析结构体
        bool parseBasic(const char* json, REQUEST_BODY_BASIC* basic);

        // <获取系统信息>请求Json解析结构体
        bool parseInfo(const char* json, REQUEST_BODY_INFO* info);

        // <复位/清零>请求Json解析结构体
        bool parseReset(const char* json, REQUEST_BODY_RESET* reset);

        // <自定义>请求Json解析结构体
        bool parseCustom(const char* json, REQUEST_BODY_CUSTOM* custom);


        // 基本应答体序列化Json
        char* printBasic(RESPONSE_BODY_BASIC* resBasic);

        // <获取系统信息>应答结构体序列化Json
        char* printInfo(RESPONSE_BODY_INFO* resInfo);

        // <获取系统信息>应答结构体序列化Json
        char* printReset(RESPONSE_BODY_RESET* resReset);

        char* printCustom(RESPONSE_BODY_CUSTOM* resCustom);


        template<class T>
        bool parse(const char* json, T *req)
        {
            return true;
        }


    };

}

#endif
