#define ECHO 12
#define TRIG 7

void setup() {
  pinMode(5,OUTPUT); //set ENA as an output
  pinMode(6,OUTPUT); //set ENB as an output
  pinMode(8,OUTPUT); //set IN1 as an output
  pinMode(9,OUTPUT); //set IN2 as an output
  pinMode(10,OUTPUT); //set IN3 as an output
  pinMode(11,OUTPUT); //set IN4 as an output
  pinMode(ECHO,INPUT); //Initialise pin 12 as an input
  pinMode(TRIG,OUTPUT); //Initialise pin 7 as an output
  Serial.begin(9600); //begin serial communication
  delay(5000);//delay before starting loop
}

void loop() {
  
  unsigned int distance_mm = 0; //This variable will hold the distance
  distance_mm = sonar_mm(); //call the function sonar_mm and store the result in distance_mm
  Serial.print("Distance="); //print the result to the serial monitor
  Serial.println(distance_mm);
  

  if (distance_mm > 200){
  leftForwards();  //see the left motor to run forwards
  rightForwards();  //set the right motor to run forwards
  analogWrite(5,140); 
  analogWrite(6,130);
  }else{
    analogWrite(6,0);
    delay (2);
    analogWrite(5,0);
  }
}
  
unsigned int sonar_mm(void){
  long duration = 0;
  const float speed_sound = 340.29;// m/s, "const" makes the compiler able to optimise the program where this variable is used, cool!
  // Read in a distance from the ultrasonic distance sensor:
  // The ultrasonic burst is triggered by a HIGH pulse of 10 microseconds.
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  //read length of time pulse
  duration = pulseIn(ECHO, HIGH); //This function measures a pulsewidth and returns the width in microseconds
  // convert the time into a distance
  // the code "(unsigned int)" turns the result of the distance calculation
  // into an integer instead of a floating point (decimal or fractional) number.
  return (unsigned int)(0.5 * duration * 1e-6 * speed_sound * 1e3); 
  //"unsigned" ensures we are returning an unsigned number, remember that there is no such thing as negative distance.
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
