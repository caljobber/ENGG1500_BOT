#include <Servo.h>
#define trigPin 7
#define echoPin 12
Servo myservo;  // create servo object to control a servo



void setup() {
  myservo.attach(4);  
  pinMode(5,OUTPUT); //set ENA as an output
  pinMode(6,OUTPUT); //set ENB as an output
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}
  int angles[] = {0, 90}; 
  int i = 0;
  long duration;
  int distance;
  int val;    // variable to read the value from the analog pin


void loop() {
  
  i = 0; 
  val = angles[i];
  myservo.write(val);
  analogWrite(5, 150);
  analogWrite(6, 150); 
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print(distance);
  Serial.println(" cm");
  
  if (distance > 5 && distance < 30) {
    analogWrite(5, 150);
    analogWrite(6, 170);
    }
  else if (distance < 5){
    analogWrite(5, 170);
    analogWrite(6, 150);
    }

}
