#include "Arduino.h"
#include <Motor.h>

Motor::Motor(int en, int in1, int in2) {
	
	_inPin1 = in1;
	_inPin2 = in2;
	_enPin  = en;
	
	pinMode(_inPin1, OUTPUT);
	pinMode(_inPin2, OUTPUT);
	
	Motor::stop();
}

void Motor::forwards(int speed) {
	
	digitalWrite(_inPin1, HIGH);
	digitalWrite(_inPin2, LOW);
	analogWrite(_enPin, speed);
}

void Motor::backward(int speed) {

	digitalWrite(_inPin1, LOW);
	digitalWrite(_inPin2, HIGH);
	analogWrite(_enPin, speed);
}

void Motor::stop() {

	digitalWrite(_inPin1, LOW);
	digitalWrite(_inPin2, LOW);
	analogWrite(_enPin, 0);
}
