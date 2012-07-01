#include <SerialGraph.h>
#include <AccelMeter.h>

SerialGraph Graph;

AccelMeter am(0, 1, 2, 8, 9, 10, 11);
int xLow  = 310;
int xHigh = 810;
int zLow  = 410;
int zHigh = 658;


void setup() {

  am.setup(G15, 315, 806, 171, 853, 390, 642);
  am.wake();
  Graph.begin(9600);
}

void loop() {

  am.setRad();

  int xDeg = ((int) (am.xRad() * RAD_TO_DEG));
  int zDeg = ((int) (am.zRad() * RAD_TO_DEG));
  
  if(xDeg < 0) {
     zDeg = -(zDeg); 
  }
  
  int angle = (xDeg + zDeg) / 2 * 1000;
  
  Graph.value(1, analogRead(0));
  Graph.value(2, analogRead(1));
  Graph.value(3, analogRead(2));
  //Graph.value(1, xDeg);
  //Graph.value(2, zDeg);
  //Graph.value(3, angle);
  Graph.print();
}

