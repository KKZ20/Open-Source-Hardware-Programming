#include <Servo.h>

int servoLpin = 9;  //left foot
int servoRpin = 10; //right foot
Servo servoL;
Servo servoR;
int posL;
int posR;

void setup()
{
    Serial.begin(9600);
    servoL.attach(servoLpin);
    servoR.attach(servoRpin);
    servoL.write(90);
    servoR.write(90);
}
void loop()
{
    // Serial.println(posL);
    // Serial.println(posR);
    for (posL = 90; posL > 70; posL -= 2)
    {
        servoL.write(posL);
        delay(10);
    }
    posL = posL - 2;
    for (posR = 90; posR < 110; posR += 2)
    {
        servoR.write(posR);
        delay(5);
        posL += 2;
        servoL.write(posL);
        delay(5);
    }
    for (posR = 110; posR > 90; posR -= 2)
    {
        servoR.write(posR);
        delay(10);
    }
}