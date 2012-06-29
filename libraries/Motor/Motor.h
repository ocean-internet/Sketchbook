#ifndef MOTOR_H
#define MOTOR_H

#include "Arduino.h"

class Motor {
	public:
		Motor(int en, int in1, int in2);
		void forwards(int speed);
		void backward(int speed);
		void stop();
		
	private:
		int _inPin1;
		int _inPin2;
		int _enPin;
};
#endif
