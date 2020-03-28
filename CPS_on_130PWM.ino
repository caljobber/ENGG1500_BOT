#include <elapsedMillis.h>
#include <ENGG1500Lib.h>
elapsedMillis timeElapsed;
unsigned int interval = 20000;

void setup() {
  pinMode(5,OUTPUT); //set ENA as an output
  pinMode(6,OUTPUT); //set ENB as an output
  pinMode(8,OUTPUT); //set IN1 as an output
  pinMode(9,OUTPUT); //set IN2 as an output
  pinMode(10,OUTPUT); //set IN3 as an output
  pinMode(11,OUTPUT); //set IN4 as an output
  enc_init();
  Serial.begin(9600);
}
void loop() {
enc_clear();//set both encoder counts to 0
while(timeElapsed < interval){
analogWrite(5,130);
analogWrite(6,130);
Serial.print(enc_getLeft());
delay(10);
}
}
