#include <elapsedMillis.h>
#include <ENGG1500Lib.h>
#include <PID_v1.h>

elapsedMillis timeElapsed;

double Setpoint, Input, Output;

double Kp= 0, Ki= 0, Kd= 0;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);


double CountsPerSecond = ((enc_getLeft())/timeElapsed)*1000;

double motorSpeed = CountsPerSecond * 91.7;

void setup() {
  Input = motorSpeed;
  Setpoint = 150;
  myPID.SetMode(AUTOMATIC);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  enc_init();
  Serial.begin(9600);
  enc_clear();

}

void loop() {
  myPID.Compute();
  analogWrite(5, Output);
  Serial.println(Output);

}


void leftForwards(void)
{
digitalWrite(8,LOW);
digitalWrite(9,HIGH);
}
