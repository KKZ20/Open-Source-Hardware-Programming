#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>

extern WiFiUDP Udp;

extern const char ssid[];
extern const char pass[];
extern const int localPort;

// configration to set up static ip address
extern IPAddress ip;
extern IPAddress gateway;
extern IPAddress subnet;

void routeMessage(OSCMessage & msg);
void connectWifi();
void sendUdp(IPAddress outIp, int outPort, char address[]);
void listenOscOnUdp();
