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
  int distance;
  int val;    // variable to read the value from the analog pin


  unsigned int sonar_mm(void){
  long duration = 0;
  const float speed_sound = 340.29;
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  duration = pulseIn(ECHO, HIGH); 
  return (unsigned int)(0.5 * duration * 1e-6 * speed_sound * 1e3);
  }

void loop() {
  
  i = 0; 
  val = angles[i];
  myservo.write(val);
  analogWrite(5, 150);
  analogWrite(6, 150); 

  unsigned int distance_mm = 0;
  distance_mm = sonar_mm();
  unsigned int mm = sonar_mm();

  Serial.print(mm);
  
  while (mm > 50 && mm < 300) {
    analogWrite(5, 150);
    analogWrite(6, 170);
    }
  while (mm < 50){
    analogWrite(5, 170);
    analogWrite(6, 150);
    }

}
