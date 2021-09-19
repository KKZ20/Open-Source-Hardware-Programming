#include "ColorSensor.h"//引用库文件
int S0 = 4; //颜色传感器上的S0
int S1 = 7; //颜色传感器上的S1
int S2 = 8; //颜色传感器上的S2
int S3 = 10; //颜色传感器上的S3
int OUT = 2; //颜色传感器上的OUT
int RPIN = 6; //RGB LED的红色针脚
int GPIN = 11; //RGB LED的绿色针脚
int BPIN = 9; //RGB LED的蓝色针脚
int r, g, b; //定义三个颜色变量
int R, G, B; //输出颜色
int threshold = 100;

void setup() {
  Serial.begin(9600);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(RPIN, OUTPUT);
  pinMode(GPIN, OUTPUT);
  pinMode(BPIN, OUTPUT);
  colorsensor_set_pins(S0, S1, S2, S3, OUT);
  //引用库文件中的函数，设置颜色传感器的四个引脚状态为输出
}

void loop() {
  colorsensor_read_color(&r, &g, &b);
  //引用库文件中的函数，读取颜色的RGB值
  Serial.print(r);
  Serial.print(", ");
  Serial.print(g);
  Serial.print(", ");
  Serial.println(b);
  if (r > threshold) {
    if (g > threshold) {
      if (b > threshold) {
        Serial.print("white");
        R = 255, G = 255, B = 255;
      } else {
        Serial.print("Yellow");
        R = 255, G = 255, B = 0;
      }
    } else if (b > threshold) {
      Serial.print("Magenta");
      R = 255, G = 0, B = 255;
    } else {
      Serial.print("Red");
      R = 255, G = 0, B = 0;
    }
  } else if (g > threshold) {
    if (b > threshold) {
      Serial.print("Cyan");
      R = 0, G = 255, B = 255;
    } else {
      Serial.print("Green");
      R = 0, G = 255, B = 0;
    }
  } else {
    if (b > threshold) {
      Serial.print("Blue");
      R = 0, G = 0, B = 255;
    } else {
      Serial.print("None");
      // r=0,g=0,b=0;
      // 没有光照时，保持原有的rgb值
    }
  }
  analogWrite(RPIN, R);
  analogWrite(GPIN, G);
  analogWrite(BPIN, B);
  delay(100);
}
