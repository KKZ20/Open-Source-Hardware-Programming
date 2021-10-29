#include <Servo.h>
#include "esp_with_osc.h"

char ssid[] = "kaiyuan_group_1"; // 网络名
char pass[] = "woaikaiyuan"; // 网络密码
int localPort = 6969; // 自己的端口号

// 设置静态ip
IPAddress ip(192, 168, 96, 110);
IPAddress gateway(192, 168, 96, 1);
IPAddress subnet(255, 255, 255, 0);

WiFiUDP Udp;

#define servoPin1 D5
Servo Servo1;

void routeMessage(OSCMessage &msg) {
  msg.route("/1/faderA", fade1);
}

void fade1(OSCMessage &msg, int addr) {
  float value = msg.getFloat(0);
  Servo1.write(100 * value);
}

void setup() {
  Serial.begin(115200);
  connectWifi();
  Servo1.attach(servoPin1);
  Servo1.write(0);
}

void loop() {
  listenOscOnUdp();
  delay(10);
}
