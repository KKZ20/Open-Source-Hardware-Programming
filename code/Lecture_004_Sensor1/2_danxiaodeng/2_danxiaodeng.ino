int soundPin=A0;
int scareVal=30;
int lightPin=2;
int lastReading=0;


void blink_bulb()
{
  digitalWrite(lightPin,LOW);
  delay(100);
  digitalWrite(lightPin,HIGH);
  delay(50);
  digitalWrite(lightPin,LOW);
  delay(80);
  digitalWrite(lightPin,HIGH);

  
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(lightPin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int soundVal=analogRead(soundPin);
  digitalWrite(lightPin,HIGH);
  Serial.println(soundVal);
  if(soundVal-lastReading>scareVal)
  {
    blink_bulb(); 
  }
  lastReading=analogRead(soundPin);
  delay(50);
}
