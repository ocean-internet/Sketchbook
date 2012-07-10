#include <KalmanFilter.h>
#include <Pid.h>
#include <Motor.h>
#include <AccelMeter.h>

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

double Kp = 2000;
double Ki = 128;
double Kd = 164;

//Specify the links and initial tuning parameters
Pid myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

int speedOffset = 64;
int motorSpeed  = 0;

Motor myMotor(3, 4, 5);

AccelMeter am(0, 1, 2, 8, 9, 10, 11);
int xLow  = 320;
int xHigh = 804;
int zLow  = 398;
int zHigh = 636;

void setup() {
  
  //initialize the variables we're linked to
  Input    = 0;
  // Higher -> board
  // Lower  -> battery
  Setpoint = 100;
  
  pinMode(13, OUTPUT);
  
  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  
  am.setup(G15, 315, 806, 171, 853, 390, 642);
  am.wake();

  myMotor.stop();
}

void loop() {
  
  am.setRad();

  double xRad = am.xRad();
  double zRad = am.zRad();
  
  if(xRad < 0) {
     zRad = -(zRad); 
  }
  
  xRad = (xRad + zRad) / 2 * 1000;
  
  Input = am.xRad() * 1000;
  myPID.Compute();
    
  if(Input < -300 || Input > 800) {
      
    myMotor.stop();
    
  } else if(Output > 0) {
    
    motorSpeed = speedOffset + Output;
    if(motorSpeed > 255) {
      motorSpeed = 255;
    }
                                                                          
    myMotor.backward(motorSpeed);
  
  } else if(Output < 0) {
    
    motorSpeed = speedOffset + (-(Output));
    if(motorSpeed > 255) {
      motorSpeed = 255;
    }
    
    myMotor.forwards(motorSpeed);
    
  } else {

    myMotor.stop();
  }
}

