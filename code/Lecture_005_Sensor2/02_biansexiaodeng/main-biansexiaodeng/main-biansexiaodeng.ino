#include "ADXL345.h"//引用库
int Xg, tempx;
int Yg, tempy;
int Zg, tempz;
int Rpin = 3;
int Gpin = 5;
int Bpin = 6;
double Xbase, Ybase, Zbase;
int X_out,Y_out,Z_out;
void setup() {
  Serial.begin(9600);
  ADXL345_init();//引用库函数，初始化传感器
  pinMode(Rpin, OUTPUT);
  pinMode(Gpin, OUTPUT);
  pinMode(Bpin, OUTPUT);
  tempx = abs((int)X_out) < 10 ? 0 : abs((int)X_out) - 10; //传感器输出值处理
  tempy = abs((int)Y_out) < 10 ? 0 : abs((int)Y_out) - 10;
  tempz = abs((int)Z_out + 260) < 10 ? 0 : abs((int)Z_out + 250);
  ADXL345_update();//引用库函数，更新数据
  Xbase = constrain(map(tempx, 0, 100, 0, 255), 0, 255);//将传感器输出的x方向加速度值映射到LED灯的亮度值
  Ybase = constrain(map(tempy, 0, 100, 0, 255), 0, 255);
  Zbase = constrain(map(tempz, 0, 100, 0, 255), 0, 255);
}

void loop() {
  ADXL345_update();//引用库函数，更新数据
  tempx = abs((int)X_out) < 10 ? 0 : abs((int)X_out) - 10; //传感器输出值处理
  tempy = abs((int)Y_out) < 10 ? 0 : abs((int)Y_out) - 10;
  tempz = abs((int)Z_out + 260) < 10 ? 0 : abs((int)Z_out + 230);
  Xg = constrain(map(tempx, 0, 100, 0, 255), 0, 255);//将传感器输出的x方向加速度值映射到LED灯的亮度值
  Yg = constrain(map(tempy, 0, 100, 0, 255), 0, 255);
  Zg = constrain(map(tempz, 0, 100, 0, 255), 0, 255);
  Serial.print("X=" );
  Serial.print(Xg - Xbase);//输出x方向的加速度变化值
  Serial.print(" ");
  Serial.print("Y= ");
  Serial.print(Yg - Ybase);
  Serial.print(" ");
  Serial.print("Z= ");
  Serial.print(Zg - Zbase);
  Serial.println(" ");
  analogWrite(Rpin, Xg - Xbase);
  analogWrite(Gpin, Yg - Ybase);
  analogWrite(Bpin, Zg - Zbase);
  delay(50);
}
