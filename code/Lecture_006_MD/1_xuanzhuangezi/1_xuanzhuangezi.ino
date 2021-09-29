int E1 = 10; //转速
int M1 = 11; //方向
int speedVal;
void setup()
{
    pinMode(M1, OUTPUT);
}
void loop()
{
    // 正转由慢变快
    for (speedVal = 100; speedVal <= 200; speedVal += 1)
    {
        digitalWrite(M1, HIGH);    //正转
        analogWrite(E1, speedVal); //PWM调速，数值越小速度越快
        delay(30);
    }
    delay(1000); // 反转由快变慢
    for (speedVal = 200; speedVal >= 100; speedVal -= 1)
    {
        digitalWrite(M1, LOW);     //反转
        analogWrite(E1, speedVal); //PWM调速，数值越大速度越快
        delay(30);
    }
    delay(1000);
}