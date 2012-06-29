#include <Pid.h>
#include <Motor.h>

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

double Kp = 5000;
double Ki = 2000;
double Kd = 1;

//Specify the links and initial tuning parameters
Pid myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

int anglePin    = 0;
int speedOffset = 32;
int motorSpeed  = 0;
int deadBand    = 4;

Motor myMotor(3, 4, 5);

void setup() {
  
  //initialize the variables we're linked to
  Input = analogRead(anglePin);
  Setpoint = 570;
  
  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  
  // Set up accellarometer
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);

  myMotor.stop();
}

void loop() {
  
  Input = analogRead(anglePin);
  myPID.Compute();
  
  int request = ((Output * 2) + 512);
  
  if(Input < 362 || Input > 762) {
      
    myMotor.stop();
    
  } else if(Output > deadBand) {
    
    motorSpeed = speedOffset + Output;
    if(motorSpeed > 255) {
      motorSpeed = 255;
    }
                                                                          
    myMotor.backward(motorSpeed);
  
  } else if(Output < -(deadBand)) {
    
    motorSpeed = speedOffset + (-(Output));
    if(motorSpeed > 255) {
      motorSpeed = 255;
    }
    
    myMotor.forwards(motorSpeed);
    
  } else {

    myMotor.stop();
  }
}

