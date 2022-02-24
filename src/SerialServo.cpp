#include <iostream>
using namespace std;

#include "SerialServo.h"

SerialServo::SerialServo() {
}

SerialServo::~SerialServo() {

}

void SerialServo::begin (unsigned long baud, uint32_t config, int8_t rxPin, int8_t txPin)
{
    Serial2.begin(baud, config, rxPin, txPin);
    Serial2.setTimeout(10);
}

void SerialServo::listen()
{
    while (Serial2.available())
    {
        requestString.clear();
        requestString = Serial2.readString();
        requestCallback();
    }
    
}

void SerialServo::onRequest(onRequestPointer pointer)
{
    requestCallback = pointer;
    self = this;
}

bool SerialServo::parse()
{
    requestData.clear();
    DeserializationError desError = deserializeJson(requestData, requestString);
    if (desError) {
        parseError = desError.c_str();
        return false;
    } else {
        parseError = "";
    }

    return true;
}

void SerialServo::response() {
    serializeJson(responseData, Serial2);
}

