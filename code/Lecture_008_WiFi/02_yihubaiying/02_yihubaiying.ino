#include "esp_with_osc.h"

char ssid[] = "kaiyuan_group_1"; // 网络名
char pass[] = "woaikaiyuan"; // 网络密码
int localPort = 6969; // 自己的端口号

// 设置静态ip
IPAddress ip(192, 168, 31, 110);
IPAddress gateway(192, 168, 31, 1);
IPAddress subnet(255, 255, 255, 0);

WiFiUDP Udp;

#define redPin D11
#define greenPin D12
#define bluePin D13
#define touchPin D10

void routeMessage(OSCMessage &msg) {
  msg.route("/1", do_state_1);
  msg.route("/2", do_state_2);
  msg.route("/3", do_state_3);
}

void do_state_1(OSCMessage &msg, int addr) {
  analogWrite(redPin, 255);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
  delay(1000);
}

void do_state_2(OSCMessage &msg, int addr) {
  analogWrite(redPin, 0);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 0);
  delay(1000);
}

void do_state_3(OSCMessage &msg, int addr) {
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 255);
  delay(1000);
}

void do_self_state() {
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 255);
}

void setup() {
  Serial.begin(115200);
  connectWifi();
}

void loop() {
  do_self_state();
  listenOscOnUdp();
  if (digitalRead(touchPin) == HIGH) {
    int var = digitalRead(touchPin);
    Serial.println(var);

    IPAddress outIp(192, 168, 96, 255);
    sendUdp(outIp, 6969, "/3");
    delay(1000);
  }
  delay(100);
}
