int ledPin1=10;
int ledPin2=11;      // 定义控制灯的亮灭的两个数字输出端口
float ledValue=255;  // 表示灯的亮度
int photoPin=A1;
int photoValue;      // 模拟端口电平值0-1023代表0-5v
int infraredPin=4;   // 数字四端口，其电平值代表红外传感器是否感应到木勺~
int infraredValue;   // 四端口的电平值，电平值为高，则代表有障碍物
int infraredState=0; // 状态值，一个状态变量，希望自己理解

void setup() {
  pinMode(ledPin1,OUTPUT);
  pinMode(ledPin2,OUTPUT);
  pinMode(infraredPin,INPUT);
  Serial.begin(9600);
}

void loop() {
  infraredValue=digitalRead(infraredPin); //获取四端口(红外传感器)的电平值
  if(infraredValue==HIGH)  //如果为高电平，则表示木勺靠近
  {
    if(infraredState==0)//状态有效
    {
      ledValue -= ledValue*2/3;   //等价于ledValue=ledValue-ledValue*2/3;
      infraredState = 1;          //关状态，一次靠近只进行一次操作
    }
    delay(200);
  }
  else 
  {
    infraredState = 0;
  }
  Serial.println(ledValue);
  photoValue = analogRead(photoPin);
  if(photoValue>950&&ledValue<252)
  {
    ledValue += 3;
    delay(50);
  }
  analogWrite(ledPin1, ledValue);
  analogWrite(ledPin2, ledValue);
}
