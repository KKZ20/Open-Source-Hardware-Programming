#include <ColorSensor.h>

int S0 = 4; //颜色传感器上的S0
int S1 = 7; //颜色传感器上的S1
int S2 = 8; //颜色传感器上的S2
int S3 = 10; //颜色传感器上的S3
int OUT = 2; //颜色传感器上的OUT
int RPIN = 6; //RGB LED的红色针脚
int GPIN = 11; //RGB LED的绿色针脚
int BPIN = 9; //RGB LED的蓝色针脚
int r, g, b;//定义三个颜色变量

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
  //设置颜色传感器的四个引脚状态为输出
}

void loop() {
  colorsensor_read_color(&r, &g, &b);
  //读取颜色的RGB值
  Serial.print(r);
  Serial.print(", ");
  Serial.print(g);
  Serial.print(", ");
  Serial.println(b);
  analogWrite(RPIN, r);
  analogWrite(GPIN, g);
  analogWrite(BPIN, b);
  delay(1000);
}
