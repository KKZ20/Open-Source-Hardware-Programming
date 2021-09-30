#include "Arduino.h"
#include "ColorSensor.h"

int s0, s1, s2, s3;
int out;
int flag = 0;
byte counter = 0;
byte countR = 0, countG = 0, countB = 0;

int red = 0, green = 0, blue = 0;

void colorsensor_set_pins(int a, int b, int c, int d, int e)
{
  s0 = a;
  s1 = b;
  s2 = c;
  s3 = d;
  out = e;
  TCS();
}

void colorsensor_read_color(int *a, int *b, int *c)
{
  *a = red;
  *b = green;
  *c = blue;
}

void TCS()
{
  flag = 0;
  digitalWrite(s1, HIGH);
  digitalWrite(s0, HIGH);
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  attachInterrupt(0, ISR_INTO, LOW);
  timer0_init();
}

void ISR_INTO()
{
  counter++;
}

void timer0_init(void)
{
  TCCR2A = 0x00;
  TCCR2B = 0x07; //the clock frequency source 1024 points
  TCNT2 = 100;   //10 ms overflow again
  TIMSK2 = 0x01; //allow interrupt
}

int i = 0;
ISR(TIMER2_OVF_vect) //the timer 2, 10ms interrupt overflow again. Internal overflow interrupt executive function
{
  TCNT2 = 100;
  flag++;
  if (flag == 1)
  {
    countR = counter;
    //    Serial.print("red=");
    //    Serial.println(countR, DEC);
    red = countR;
    digitalWrite(s2, HIGH);
    digitalWrite(s3, HIGH);
  }
  else if (flag == 2)
  {
    countG = counter;
    //    Serial.print("green=");
    //    Serial.println(countG, DEC);
    green = countG;
    digitalWrite(s2, LOW);
    digitalWrite(s3, HIGH);
  }
  else if (flag == 3)
  {
    countB = counter;
    //    Serial.print("blue=");
    //    Serial.println(countB, DEC);
    blue = countB;
    //    Serial.println("\n");
    digitalWrite(s2, LOW);
    digitalWrite(s3, LOW);
  }
  else if (flag == 4)
  {
    flag = 0;
  }
  counter = 0;
}
