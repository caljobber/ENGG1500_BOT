const int IRS1=A1;
  int inputVal = 0;
//START
void setup() {
  // put your setup code here, to run once:
  pinMode(5,OUTPUT); //set ENA as an output
  pinMode(6,OUTPUT); //set ENB as an output
  pinMode(8,OUTPUT); //set IN1 as an output
  pinMode(9,OUTPUT); //set IN2 as an output
  pinMode(10,OUTPUT); //set IN3 as an output
  pinMode(11,OUTPUT); //set IN4 as an output
  Serial.begin(9600);
  
  delay(5000);//delay before starting loop
}

void loop() {
  inputVal = analogRead(IRS1);
  Serial.println(inputVal);
  if (analogRead(IRS1) < 100){
  leftForwards();  //see the left motor to run forwards
  rightForwards();  //set the right motor to run forwards
  analogWrite(5,200); 
  analogWrite(6,200);
  }else{
    analogWrite(5,0);
    delay (2);
    analogWrite(6,0);
  }
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
//END
