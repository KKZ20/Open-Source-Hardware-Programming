int trigPin=4;
int echoPin=3;
int ledPin=6;
int baseDistance=5;
float distance=0;
int ledValue;

void setup(){
  Serial.begin(9600);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(ledPin,OUTPUT);
}
void loop(){
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  distance = pulseIn(echoPin,HIGH)/58.0;
  if(distance>baseDistance){
    ledValue=map(distance,5,20,0,255);
  }
  analogWrite(ledPin,ledValue);
  Serial.println(distance);
}
