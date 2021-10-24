/* Send and receive OSC message via udp
 *  See: 
 *  Example code for ESP8266WiFi Udp: https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/examples/Udp/Udp.ino
 *  OSC for Arduino: https://github.com/CNMAT/OSC
 */

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>

const char ssid[] = "your ssid";
const char pass[] = "your password";
const int localPort = 6000;

// configration to set up static ip address
IPAddress ip(192, 168, 96, 100);
IPAddress gateway(192, 168, 96, 1);
IPAddress subnet(255, 255, 255, 0);

WiFiUDP Udp;

// setup the callback functions you want to exexute when receiving message
// See: https://github.com/CNMAT/OSC#routing--dispatching
void routeMessage(OSCMessage &msg) {
  msg.route("/yourturn", callback);
  msg.route("/other", callback2);
}

void callback(OSCMessage &msg, int addr) {
  Serial.println("received message.");
}

void callback2(OSCMessage &msg, int addr) {
  Serial.println("other callback");
}

void setup() {
  Serial.begin(115200);

  // set up connection and print to serial monitor
  wifiConnect();
}

void loop() {
  // listen the incoming udp packet
  listenOscOnUdp();

  // send udp message to other devices
  IPAddress outIp(192, 168, 96, 110);
  // sendUdp(outIp, 6000, "/yourturn");
  sendUdp(outIp, 6000, "/other");

  delay(500);
}

void wifiConnect() {
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.config(ip, gateway, subnet); // config static ip, needs three arguments
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Starting UDP");
  Udp.begin(localPort);
  Serial.print("Local port: ");
  Serial.println(Udp.localPort());
}

// See: https://github.com/CNMAT/OSC/blob/master/examples/ESP8266sendMessage/ESP8266sendMessage.ino
void sendUdp(IPAddress outIp, int outPort, char address[]) {
  OSCMessage msg(address);
  Udp.beginPacket(outIp, outPort);
  msg.send(Udp);
  Udp.endPacket();
  msg.empty();
}

// See: https://github.com/CNMAT/OSC/blob/master/examples/ESP8266ReceiveMessage/ESP8266ReceiveMessage.ino
void listenOscOnUdp() {
  OSCMessage msg;
  int size;

  if ((size = Udp.parsePacket()) > 0) {
    while (size--)
      msg.fill(Udp.read());

    if (!msg.hasError())
      routeMessage(msg);
  }
}
