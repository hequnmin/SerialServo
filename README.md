
# SerialServo

 - ESP32 简易串口通讯服务，通讯指令解析。

## 特征
 - [x] 支持ESP32、ESP8266;
 - [x] Uart定义, RX/TX 引脚自定义, 通讯监听;
 - [x] 接收事件回调，应答发送后事件回调;
 - [x] 请求结构体/应答结构体的序列化/反序列化;


## 应用与实例
 - platformio.ini
```
lib_deps = 
    https://github.com/hequnmin/SerialServo.git        
```

 - SerialServo 实例
```cpp
#include <Arduino.h>
#include "SerialServo.hpp"

SerialServo srv;

void onRequest() {
    Serial.println((char *)srv.buffer);
    srv.response("Hello World!");
}

void setup() {
    Serial.begin(115200);

    // SerialServo Setup
    srv.uartNum = SRV_UART_NUM_0;   // UartNum，Default: SRV_UART_NUM_1
    srv.begin(115200, 5, 18);       // RX = 5; TX = 18;
    srv.onRequest(onRequest);       // Callback
}

void loop() {
    srv.listen();
}
```

 - Command 实例
```cpp
#include <Arduino.h>
#include "Command.hpp"

Command cmd;
void setup() {
    Serial.begin(115200);
}

void loop() {
    REQUEST_BODY_BASIC reqBasic;
    if (cmd.parseBasic("{\"id\":123,\"cmd\":\"info\"}", &reqBasic)) {
        RESPONSE_BODY_BASIC resBasic;
        resBasic.err = NULL;
        resBasic.id = reqBasic.id;
        Serial.println(cmd.printBasic(&resBasic));
    } else {
        Serial.println("parse failed!");
    }
}

```
