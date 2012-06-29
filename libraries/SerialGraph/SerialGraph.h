#ifndef SERIAL_GRAPH_H
#define SERIAL_GRAPH_H

#include "Arduino.h"

class SerialGraph {

  public:
    SerialGraph();
    void begin(int baudRate);
    void update();
    void value(int channel, int value);
    void print();
    
  private:
    int _channel1;
    int _channel2;
	int _channel3;
	String formatGraph();
	String channel(int value, int offset=0);
};
#endif
