#include <iostream>
#include <Arduino.h>
#include "SerialServo.hpp"

using namespace std;

#define RXD2 5
#define TXD2 18

SerialServo srv;

void onRequest()
{
    bool ok = srv.parse();

    if (ok) {
        // srv.responseData.clear();
        // srv.responseData["err"] = String();
        // srv.responseData["cmd"] = srv.requestData["cmd"].as<String>();

    } else {
        // srv.responseData.clear();
        // srv.responseData["err"] = srv.parseError;
    } 

    srv.response();
}

void setup() {
    // put your setup code here, to run once:
    Serial.begin (115200);
    Serial.println ();

    // 串口伺服设置
    srv.begin(115200, SERIAL_8N1, RXD2, TXD2);

    // 接收指令回调函数
    srv.onRequest(onRequest);

}

void loop() {
    // put your main code here, to run repeatedly:
    // Serial.println("Hello World!");
    // delay(1000);

    // 串口伺服监听
    srv.listen();

}