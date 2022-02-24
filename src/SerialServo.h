

#ifndef SerialServo_h
#define SerialServo_h

#include <iostream>
using namespace std;

#include <Arduino.h>
#include <ArduinoJson.h>

#define RXD2 5
#define TXD2 18

class SerialServo;
typedef void (*onRequestPointer) ();

class SerialServo
{
    
public:
    SerialServo();
    ~SerialServo();

public:
    String requestString = String();
    String responseString = String();

    StaticJsonDocument<1024>  requestData;
    StaticJsonDocument<1024>  responseData;

    // 串口设置
    void begin(unsigned long baud = 115200, uint32_t config = SERIAL_8N1, int8_t rxPin = 5, int8_t txPin = 18);

    // 串口监听
    void listen();

    // 串口接收数据后回调函数
    void onRequest(onRequestPointer pointer);

    // 通信内容解析：JSON反序列化（暂时不支持校验参数有效性），true: 成功；false：失败，parseError：失败原因。
    bool parse();
    const char* parseError;

    void response();

private:
    onRequestPointer requestCallback;
    SerialServo *self;
};



#endif
