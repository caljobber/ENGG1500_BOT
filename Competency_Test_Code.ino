
#include <ENGG1500Lib.h>
#define ECHO 7
#define TRIG 12

void setup() {
pinMode(5,OUTPUT); 
pinMode(6,OUTPUT); 
pinMode(8,OUTPUT); 
pinMode(9,OUTPUT); 
pinMode(10,OUTPUT); 
pinMode(11,OUTPUT); 
enc_init();

pinMode(A1,INPUT);
Serial.begin(9600);

pinMode(ECHO,INPUT); 
pinMode(TRIG,OUTPUT); 
Serial.begin(9600);} 

unsigned int sonar_mm(void){
long duration = 0;
const float speed_sound = 340.29;
digitalWrite(TRIG, HIGH);
delayMicroseconds(10);
digitalWrite(TRIG, LOW);
duration = pulseIn(ECHO, HIGH); 
return (unsigned int)(0.5 * duration * 1e-6 * speed_sound * 1e3);
}

void leftForwards(void)
{
digitalWrite(8,LOW);
digitalWrite(9,HIGH);
}
void leftBackwards(void)
{
digitalWrite(8,HIGH);
digitalWrite(9,LOW);
}
void rightForwards(void)
{
digitalWrite(10,LOW);
digitalWrite(11,HIGH);
}

void rightBackwards(void)
{
digitalWrite(10,HIGH);
digitalWrite(11,LOW);
}


void loop() {
leftForwards();
rightForwards();
analogWrite(5, 130);
analogWrite(6,130);

int sensorVal = digitalRead(A1);
if (sensorVal == 1){
  analogWrite(5, 0);
  analogWrite (6,0);
}

unsigned int distance_mm = 0;
distance_mm = sonar_mm();
unsigned int mm = sonar_mm();
if(mm < 150)
{ 
enc_clear();
leftBackwards();
rightBackwards();
while((enc_getLeft()+enc_getRight())/2 < 15){
analogWrite(5,130);
analogWrite(6,130);}

analogWrite(5,0);
analogWrite(6,0);
delay(200);
enc_clear();
leftForwards();
rightForwards();
while((enc_getLeft()+enc_getRight())/2 < 30){
analogWrite(5,130);
analogWrite(6,200);}

} }
