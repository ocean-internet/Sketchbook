#include "Arduino.h"
#include "SerialGraph.h"

SerialGraph::SerialGraph() {

}

void SerialGraph::begin(int baudRate=9600) {
	Serial.begin(9600);
}

void SerialGraph::value(int channel, int value) {
	switch(channel) {
		case 1:
			_channel1 = value;
			break;
		case 2:
			_channel2 = value;
			break;
		case 3:
			_channel3 = value;
			break;
	}
}

void SerialGraph::print() {

	String graph;
	graph = formatGraph();	
	Serial.print(graph + "\r\n");
}

String SerialGraph::formatGraph() {

	String rtn = "ch1: " + channel(_channel1, 512) + _channel1 + " ch2: " + channel(_channel2, 512) + _channel2 + " ch3: " + channel(_channel3, 512) + _channel3;

	return rtn;
}

String SerialGraph::channel(int value, int offset) {
	
	String rtn;

	value += offset;

	if(value > 1024) {
		value = 1024;
	} else if(value < 0) {
		value = 0;
	}
	value = int(value / 16);
	int pad = 64 - value;

	for(int i=0; i<value; i++) {

		rtn += "*";
		if(i == 31) {
			rtn += "|";
		}	
	}

	for(int i=0; i<pad; i++) {

		if(i>0 && (pad-i) == 32) {
			rtn += "|";
		}
		rtn += ".";
	}
	
	return rtn;
}
