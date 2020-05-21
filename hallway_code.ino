#include <Servo.h>
#define TRIG 12
#define ECHO 7
Servo myservo;  // create servo object to control a servo

void setup() {
  myservo.attach(4);  
  pinMode(5,OUTPUT); //set ENA as an output
  pinMode(6,OUTPUT); //set ENB as an output
  pinMode(8,OUTPUT); //set IN1 as an output
  pinMode(9,OUTPUT); //set IN2 as an output
  pinMode(10,OUTPUT); //set IN3 as an output
  pinMode(11,OUTPUT); //set IN4 as an output
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  Serial.begin(9600);
  delay(100);
}
  int angles[] = {180}; 
  int i = 0;
  int distance;
  int val;    // variable to read the value from the analog pin



void loop() {
  // SERVO CONTROL
  i = 0; 
  val = angles[i];
  myservo.write(val);

  // SETTING UP AVERAGES 
  unsigned int distance_mm = 0;
  float dataPoints[3]; 
  float ave = 0;

  //CALCULATING AVERAGES
  for(i = 0; i<3; i++){
    dataPoints[i] = sonar_mm();
    ave = dataPoints[i]+ ave;
    delay(10); 
  }

  //PRINTING ave and calling motor functions
  ave = ave/3; 
  Serial.print("Distance ave=");
  Serial.println(ave);
  leftForwards();  
  rightForwards();


 // CHECKING DISTANCE AND TURNING
 if (ave > 50 && ave < 300){
    analogWrite(5, 150);
    analogWrite(6, 170);
 }
 if (ave < 50){
    analogWrite(5, 170);
    analogWrite(6, 150);
 }

} 
// END VOID LOOP


unsigned int sonar_mm(void){
  long duration = 0;
  const float speed_sound = 340.29;
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  duration = pulseIn(ECHO, HIGH); 
  return ((unsigned int)(0.5 * duration * 1e-6 * speed_sound * 1e3));
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
