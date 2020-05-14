#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int val;    // variable to read the value from the analog pin

void setup() {
  myservo.attach();  
  pinMode(5,OUTPUT); //set ENA as an output
  pinMode(6,OUTPUT); //set ENB as an output
}

int angles[] = {0, 90}; 
int i = 0;

void loop() {
   
{
  i = 0; 
}
val = angles[i];
myservo.write(val);                  // sets the servo position according to the scaled value
  delay(800);  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print(distance);
  Serial.println(" cm");
  if (distance > 5) {
    analogWrite(5, 130);
    analogWrite(6, 150);
  }
  else {
    analogWrite(5, 150);
    analogWrite(6, 130);
  }
}
