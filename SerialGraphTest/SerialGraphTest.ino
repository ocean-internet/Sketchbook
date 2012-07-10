#include <SerialGraph.h>

SerialGraph Graph;

void setup() {
  
  Graph.begin(9600);
  
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);

}

void loop() {
  
  Graph.value(1, analogRead(3));
  Graph.value(2, analogRead(4));
  Graph.value(3, analogRead(5));
  Graph.print();
}
