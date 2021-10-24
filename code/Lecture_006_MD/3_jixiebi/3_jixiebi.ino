#include <Stepper.h>
int potVal1 = 400;
Stepper myStepper1(potVal1, 8, 9, 10, 11);
int lightVal = 0;
void setup()
{
    myStepper1.setSpeed(100);
    Serial.begin(9600);
}

void loop()
{
    lightVal = analogRead(A1);
    if (lightVal > 200)
    {
        Serial.print("1");
        myStepper1.step(potVal1);
        delay(500);
        myStepper1.step(-potVal1);
        delay(500);
    }
    else if (lightVal <= 200)
    {
        Serial.print("0");
    }
}