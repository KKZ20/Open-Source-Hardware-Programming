int L=131;
int H=262;
int buzzerPin=3;
int trigPin=12;
int echoPin=11;
int distance;
float time;
void setup(){
  pinMode(buzzerPin,OUTPUT);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  Serial.begin(9600);
}
void loop(){
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  time=pulseIn(echoPin,HIGH);
  distance=time/58.0;
  Serial.println(distance);
  if(distance<=20){
    tone(3,L,500);
    delay(100);
  }
  else if(distance>25&&distance<=50){
    tone(3,H,500);
    delay(100);
  }
}
