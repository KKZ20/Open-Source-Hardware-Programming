#include "esp_with_osc.h"

char ssid[] = "kaiyuan_group_1";
char pass[] = "woaikaiyuan";
int localPort = 6000;

// 设置静态ip
IPAddress ip(192, 168, 96, 110);
IPAddress gateway(192, 168, 96, 1);
IPAddress subnet(255, 255, 255, 0);

WiFiUDP Udp;

#define lightPin D13
#define touchPin D10

void routeMessage(OSCMessage &msg) {
  msg.route("/yourturn", blink1);
}

void blink1(OSCMessage &msg, int addr) {
  digitalWrite(lightPin, LOW);
  delay(100);
  digitalWrite(lightPin, HIGH);
  delay(100);
  digitalWrite(lightPin, LOW);
  delay(100);
  digitalWrite(lightPin, HIGH);
  delay(100);
}

void setup() {
  Serial.begin(115200);
  connectWifi();
  pinMode(lightPin, OUTPUT);
  digitalWrite(lightPin, LOW);
}

void loop() {
  listenOscOnUdp();

  // 小组其他的ip地址
  int ip_group[7] = {16, 25, 42, 43, 48, 105, 114};
  
  if (digitalRead(touchPin) == HIGH) {
    int var = digitalRead(touchPin);
    Serial.println(var);
    int i = random(7);

    IPAddress outIp(192, 168, 96, ip_group[i]);
    sendUdp(outIp, 6000, "/yourturn");

    digitalWrite(lightPin, LOW);
    delay(1000);
  }
  delay(100);
}
