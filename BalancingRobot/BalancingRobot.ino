#include <Pid.h>

//Define Variables we'll be connecting to
double Setpoint, Input, Output;
double Kp = 2;
double Ki = 5;
double Kd = 1;
int controllerDirection = DIRECT;

//Specify the links and initial tuning parameters
Pid myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup() {
  Serial.begin(9600);
  
  //initialize the variables we're linked to
  Input    = analogRead(0);
  Setpoint = 100;
  
  //turn the PID on
  myPID.SetMode(AUTOMATIC);
}

void loop() {
  if (Serial.available() == 3) {
    
    char buffer[3];
    
    buffer[0] = Serial.read();
    buffer[1] = Serial.read();
    buffer[2] = Serial.read();
    
    int value = atoi(buffer);
    
    if(value > 255) {
      value = 255;
    } else if(value < 0) {
      value = 0;
    }
    
    Setpoint = value;
    
    Serial.print("Setpoint: ");
    Serial.println(Setpoint);
    
    Serial.print("Input: ");
    Serial.println(Input);
    
    Serial.print("Output: ");
    Serial.println(Output);
  }
  
  double error = Setpoint - Input;
  
  Input = Input + (error / 2); //analogRead();
  myPID.Compute();
  analogWrite(3, Output);
}
