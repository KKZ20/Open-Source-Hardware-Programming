# Lecture 08 通信

## Requirements

- 开发板: WEMOS D1 (esp8266 WiFi 模块)
- Arduino库: OSC
- 手机端软件: TouchOSC

### 添加第三方开发板定义

> 百度网盘：  
> 链接：https://pan.baidu.com/s/1HldqUBsXfgJARYr3VKh4kg  
> 提取码：uwy4  

Arduino IDE 菜单 > 文件 > 首选项 > 附加开发板管理Urls

添加 http://arduino.esp8266.com/stable/package_esp8266com_index.json

打开菜单 > 工具 > 开发板 > 开发板管理器，搜索 esp8266 点击安装

安装完成后即可使用开发板，在菜单 > 工具 > 开发板子菜单下选择 ESP8266 Boards > \*LOLIN(WeMos) D1 R1

> \*注：根据安装的库版本不同，开发板的名称可能不同

### 安装库 OSC(Open Sound Control)

Arduino IDE 菜单 > 工具 > 库管理器，搜索 OSC 并安装

### 开发板usb串口驱动

windows系统下已发现开发板usb串口未识别的情况，尝试安装CH340G usb芯片驱动: https://github.com/nodemcu/nodemcu-devkit/tree/master/Drivers

windows驱动已上传仓库，macOS尚未测试，Arch Linux未发现此问题

### TouchOSC

安卓端需要安装google play商店，售价$4.99

从网络获取安装包apk: https://android-apk.org/net.hexler.touchosc_a/38895697-ewan-hemingway-touchosc/

apk文件已上传仓库

苹果端使用课件中AppleID登陆appstore下载即可

## Usage

> 参考:
> - ESP8266WiFi库，udp示例代码: https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/examples/Udp/Udp.ino  
> - OSC库使用文档: https://github.com/CNMAT/OSC  

结合上述链接查看仓库内示例代码 udp_config.ino

### 使用udp协议连接wifi

```c
#include <ESP8266WiFi.h>
#include <WiFiUdp.h> // 引入WiFiUDP对象的定义

const char ssid[] = "your ssid";
const char pass[] = "your password";
const int localPort = 6000;

WiFiUDP Udp; // 声明udp对象
WiFi.begin(ssid, pass); // 连接wifi
Udp.begin(localPort); // 在端口初始化udp对象
```

Arduino官方自带用于Arduino WiFi Shield的WiFi.h库。D1板使用esp8266模块，引用ESP8266WiFi.h，其中对象的许多方法与官方库大同小异，但是在一些部分存在差异。使用时需要注意。

Arduino WiFi library: https://www.arduino.cc/en/Reference/WiFi

### 设置静态ip

使用上一章节的代码可以使开发板成功连接wifi，但是由于没有对连接进行配置，会由网关为其动态分配ip地址（DHCP）。而这使得我们不仅无法事先确定设备的ip地址，同时也无法保证重联后设备的地址不发生改变。

而为了向其他的设备定向发送数据，同时接收其他设备的数据，必须确定接收方的ip地址，因此需要为开发板配置静态ip。

```c
IPAddress ip(192, 168, 96, 100); // 设备ip地址
IPAddress gateway(192, 168, 96, 1); // 网关
IPAddress subnet(255, 255, 255, 0); // 子网掩码

WiFi.config(ip, gateway, subnet); // 配置连接参数
WiFi.begin(ssid, pass); // *在调用WiFi.begin()之前先调用WiFi.config()
```

`IPAddress` 类，四字节数组。

`WiFi.config()`方法。**调用方式与官方库不同!! 官方库定义: https://www.arduino.cc/en/Reference/WiFiConfig**

`WiFi.config(IPAddress ip, IPAddress gateway, IPAddress subnet)`

需要传入**三个参数**，均为四字节数组，分别设置本地ip，网关和子网掩码

> \*注：请在调用WiFi.begin()前调用WiFi.config()，否则wifi仍然会以DHCP模式初始化。

### OSCMessage

OSCMessage.h库提供了构造和处理OSC信息的功能，查看https://github.com/CNMAT/OSC#API

```
#include <OSCMessage.h>

// 通过udp发送信息
// https://github.com/CNMAT/OSC/blob/master/examples/ESP8266sendMessage/ESP8266sendMessage.ino
void sendUdp(IPAddress outIp, int outPort, char address[]) {
  OSCMessage msg(address);
  Udp.beginPacket(outIp, outPort);
  msg.send(Udp);
  Udp.endPacket();
  msg.empty();
}

// 接收udp包并构造osc信息
// https://github.com/CNMAT/OSC/blob/master/examples/ESP8266ReceiveMessage/ESP8266ReceiveMessage.ino
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

// msg.route()方法将会匹配osc消息的地址并执行对应的函数
// setup the callback functions you want to exexute when receiving message
// See: https://github.com/CNMAT/OSC#routing--dispatching
void routeMessage(OSCMessage &msg) {
  msg.route("/yourturn", callback);
  msg.route("/other", callback2);
}

void callback(OSCMessage &msg, int addr) {
  Serial.println("received message.");
}
```

## TODO

- [ ] 参考课件将通用代码封装入库"esp_with_osc.h"
- [ ] 修改课件
