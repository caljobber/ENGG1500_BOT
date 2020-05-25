#include <Servo.h>
#define TRIG 12
#define ECHO 7
Servo myservo;  // create servo object to control a servo

#include <stdio.h>
#include <ENGG1500Lib.h>
float IRS1=A3;//left to right of bot
float IRS2=A2;
float IRS3=A1;
float IRS4=A0;

float i1, i2, i3, i4 = 0;
float lineposition(void);
float x1 = 22 , x2 = 7, x3 = -7, x4 = -22;//measurements in mm
float xline;
float linediff;
float delaytime;
float array[5] = {0};
float sum;
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

  ----------------------------------SETUP STATE MACHINE--------------------
  switch(state) {
    case 1: //line following 
      j = 1;
      val = angles[j];
      myservo.write(val)
      i1 = analogRead(IRS1); //Gather values for 4 IR sensors
      i2 = analogRead(IRS2);
      i3 = analogRead(IRS3);
      i4 = analogRead(IRS4);
      //Serial.println(i1);
      //Serial.println(i2);
      //Serial.println(i3);
      //Serial.println(i4);
      //Serial.println("segment");
      delay (1000);
      sum = 0;
      lineposition();
      if(i1 < x && i2 < x && i3 < x && i4 < x) {
        distance = sonar_mm();
        if (distance > 200){
          state = 2;
        }
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
      
     // CHECKING DISTANCE AND TURNING
      if (ave > 50 && ave < 300){
         analogWrite(5, 150);
         analogWrite(6, 170);
      }
      if (ave < 50){
         analogWrite(5, 170);
         analogWrite(6, 150);
      }
    case 3: //distraction lines
    case 4: //diverging paths
    case 5: //end box
    
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

//--------------------------------------------------line position function------------------------------------------

float lineposition(void){
    //need to read the values from each sensor and initialise them as w1,w2,w3,w4

        xline = ((i1*x1 + i2*x2 + i3*x3 + i4*x4)/(i1 + i2 + i3 + i4));
        array[0]= array[1];
        array[1]= array[2];
        array[2]= array[3];
        array[3]= array[4];
        array[4]= xline;
        //Serial.println(xline);
        for(i=0;i<5;i++){//sum the 5 elements in the array, this is the first case
        sum+= array[i];
        //Serial.println(sum);
        }
        sum/=5;
        Serial.println(sum); 
}
