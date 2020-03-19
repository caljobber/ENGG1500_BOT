#include <ENGG1500Lib.h>
#define ENA 5
#define ENB 6
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11

void setup() {
  // put your setup code here, to run once:
  pinMode(ENA, OUTPUT); //set ENA as an output
  pinMode(ENB, OUTPUT); //set ENB as an output
  pinMode(IN1, OUTPUT); //set IN1 as an output
  pinMode(IN2, OUTPUT); //set IN2 as an output
  pinMode(IN3, OUTPUT); //set IN3 as an output
  pinMode(IN4, OUTPUT); //set IN4 as an output
  enc_init(); //initialise encoders
  delay(2000);
  Serial.begin(9600);
  Serial.println("PWM,ENC_L,ENC_R");
  //TODO: set motor direction
}
  unsigned int pwml = 165; // left volatage
  unsigned int pwmr = 140; // right volatage

void loop() {
  // put your main code here, to run repeatedly:
    leftForwards(); // defining the fucntions
    rightForwards();
    analogWrite(5,pwml); // left motor
    analogWrite(6,pwmr); // right motor
    delay (1500);
    
    if (enc_getLeft() > enc_getRight()){
    pwml--;
    }else if (enc_getLeft() < enc_getRight()){
    pwml++;
    }
    
       
    //print pwm and encoder values to the serial monitor in CSV format:
    Serial.print(pwml);
    Serial.print(",");
    Serial.print(enc_getLeft());
    Serial.print(",");
    Serial.print(pwmr);
    Serial.print(",");
    Serial.println(enc_getRight());
 enc_clear();
}  

void leftForwards(void) //This function sets IN1 = LOW and IN2 = HIGH in order to set the direction to forwards for motor 1
{
  digitalWrite(8, LOW); //IN1
  digitalWrite(9, HIGH); //IN2
}
void leftBackwards(void) //This function sets IN1 = HIGH and IN2 = LOW in order to set the direction to backwards for motor 1
{
  digitalWrite(8, HIGH); //IN1
  digitalWrite(9, LOW); //IN2
}
void rightForwards(void) //This function sets IN3 = LOW and IN4 = HIGH in order to set the direction to forwards for motor 2
{
  digitalWrite(10, LOW); //IN3
  digitalWrite(11, HIGH); //IN4
}
void rightBackwards(void) //This function sets IN3 = HIGH and IN4 = LOW in order to set the direction to forwards for motor 2
{
  digitalWrite(10, HIGH); //IN3
  digitalWrite(11, LOW); //IN4
}
