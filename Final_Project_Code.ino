#include <Servo.h>
#define TRIG 12
#define ECHO 7
#include <stdio.h>
#include <ENGG1500Lib.h>
#define ENA 5
#define ENB 6
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11
Servo myservo;  // create servo object to control a servo

#include <stdio.h>
#include <ENGG1500Lib.h>
float IRS1=A3;//left to right of bot
float IRS2=A2;
float IRS3=A1;
float IRS4=A0;

//-------------------------------For PID--------------------
float x1 = -22.5;
float x2 = -7.5;
float x3 = 7.5;
float x4 = 22.5;
float w1;
float w2;
float w3;
float w4;

const float goal = 0; 
float Ed = 0;
float Kp = 4;
float Kd = 18;
float prevE = 0;
float newE = 0;
float linedist = 0; //taken from which ir sensor is active
float den;
float num;
int i;
const int maxarr = 5;
float distarr[maxarr] = {0.0f};
float ave = 0;
/* 
//========================================\\
//THESE VALUES WERE 96 and 85 respectively\\
//========================================\\
 */

float basevall = 88;
float basevalr = 77;
float limitl = 150; 
float limitr = 120;
float pwml, pwmr;

//----------------------------------------for servo-------------

int i;

void setup() {
  myservo.attach(4);  
  pinMode(5,OUTPUT); //set ENA as an output
  pinMode(6,OUTPUT); //set ENB as an output
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(8,OUTPUT); //set IN1 as an output
  pinMode(9,OUTPUT); //set IN2 as an output
  pinMode(10,OUTPUT); //set IN3 as an output
  pinMode(11,OUTPUT); //set IN4 as an output
  
  Serial.begin(9600);
  delay(10);
}
  int angles[] = {180, 90, 0}; 
  int j = 0;
  int distance;
  int val;    // variable to read the value from the analog pin

  int state = 1;



void loop() {

  float pwml = 96;
  float pwmr = 85;

  i1 = analogRead(IRS1); //Gather values for 4 IR sensors
  i2 = analogRead(IRS2);
  i3 = analogRead(IRS3);
  i4 = analogRead(IRS4);
  ----------------------------------SETUP STATE MACHINE--------------------
  switch(state) {
    case 1: //line following 
      j = 1;
      val = angles[j];
      myservo.write(val)
 
      w1 = analogRead(IRS1); //Gather values for 4 IR sensors
      w2 = analogRead(IRS2);
      w3 = analogRead(IRS3);
      w4 = analogRead(IRS4);

      num = (w1*x1 + w2*x2 + w3*x3 + w4*x4);
      den = (w1 + w2 + w3 + w4);
      linedist = num/den;

      for (i = 0; i < maxarr; i++){
         distarr [i] = distarr [i + 1];
      }
      distarr[maxarr - 1] = linedist;
      for( i = 0, ave = 0; i < maxarr; i++){
        ave += distarr[i];
      }
      ave /= maxarr;
    
      newE = goal - ave;
      Ed = newE - prevE;        
      prevE = newE;             
  
      pwml = basevall - newE*Kp - Ed*Kd;
      pwmr = basevalr + newE*Kp + Ed*Kd;
  
      
      if (pwml > limitl){
        pwml = limitl;           
      }
      if (pwmr > limitr){
        pwmr = limitr;
      }
  
      leftForwards(); // defining the fucntions
      rightForwards();

      if (pwml < 0){
        leftBackwards();
        pwml *= -1;
      }
      if (pwmr < 0){
        rightBackwards();
        pwml *= -1;  
      }
  
      Serial.print("L");
      Serial.println(pwml);
      Serial.print("R");
      Serial.println(pwmr);
   
      analogWrite(5,pwml); // left motor
      analogWrite(6,pwmr); // right motor


      //Test for line disappearance
      if(i1 < x && i2 < x && i3 < x && i4 < x) {
        distance = sonar_mm();
        if (distance > 80){
          state = 2;
        }
        else{
          state = 4;
        }
      }
      
      //Test for presence of distraction lines
      if(i1>y && i2>y && i3>y && i4<x){
        state = 3;
      }
      break;
    
    case 2: //hallway
      j = 0; 
      val = angles[j];
      myservo.write(val);
      //SETTING UP AVERAGES
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

      analogWrite(5,pwml); // left motor
      analogWrite(6,pwmr); // right motor
      
     // CHECKING DISTANCE AND TURNING
      if (ave > 50 && ave < 300){
         analogWrite(5, pwm1);
         analogWrite(6, (pwmr+10));
      }
      if (ave < 50){
         analogWrite(5,(pwm1+10));
         analogWrite(6,pwmr);
      }
      if (i1>0 || i2>0 || i3>0 || i4>0){
        state = 1;
      }
    break;
    
    case 3: //90 degree left turn
      analogWrite(6,0);
      analogWrite(5,pwm1);
      if(ir1<x){
        state = 1;
      }
      break;
    
    case 4: //end box
      analogWrite(6,0);
      analogWrite(5,0);
      break;
  }
}


//--------------------------------DISTANCE FUNCTION----------------
unsigned int sonar_mm(void){
 long duration = 0;
 const float speed_sound = 340.29;
 digitalWrite(TRIG, HIGH);
 delayMicroseconds(10);
 digitalWrite(TRIG, LOW);
 duration = pulseIn(ECHO, HIGH); 
 return (unsigned int)(0.5 * duration * 1e-6 * speed_sound * 1e3);
 }


//--------------------------------MOTOR FUNCTIONS------------------
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
