#include <SerialGraph.h>
#include <AccelMeter.h>

SerialGraph Graph;

AccelMeter am(0, 1, 2, _1_5G, 0, 6, 0, 7);

void setup() {

  am.setup();
  am.wake();
  Graph.begin(9600);
}

void loop() {

  am.setRad();
  
  int xDeg = ((int) (am.xRad() * RAD_TO_DEG));
  int yDeg = ((int) (am.yRad() * RAD_TO_DEG));
  int zDeg = ((int) (am.zRad() * RAD_TO_DEG));
  
  Graph.value(1, xDeg);
  Graph.value(2, yDeg);
  Graph.value(3, zDeg);
  Graph.print();
}
