#include <AccelMeter.h>

// kP = 2550 - full power @ +/-5 degrees
AccelMeter::AccelMeter(
	int xOut, int yOut, int zOut, bool range,
	int selfTest, int gSelect, int zgDetect, int nSleep
) {

	_xOut     = xOut;
	_yOut     = yOut;
	_zOut     = zOut;

	setRange(range);

	_selfTest = selfTest;
	_gSelect  = gSelect;
	_zgDetect = zgDetect;
	_nSleep   = nSleep;
}

void AccelMeter::setup() {

	pinMode(_selfTest, OUTPUT);
	pinMode(_gSelect,  OUTPUT);
	pinMode(_zgDetect, OUTPUT);
	pinMode(_nSleep,   OUTPUT);
}

void AccelMeter::sleep() {

	digitalWrite(_nSleep, LOW);
}

void AccelMeter::wake() {
	
	digitalWrite(_nSleep, HIGH);
}

double AccelMeter::xG() {

	return _xG;
}
double AccelMeter::xRad() {

	return _xRad;
}

double AccelMeter::yG() {

	return _yG;
}
double AccelMeter::yRad() {

	return _yRad;
}

double AccelMeter::zG() {

	return _zG;
}
double AccelMeter::zRad() {

	return _zRad;
}

bool AccelMeter::zeroG() {

	return digitalRead(_zgDetect);
}

void AccelMeter::setRange(bool range) {

	digitalWrite(_gSelect, range);
	if(range == _1_5G) {

		_range = 1.5;
	} else {
		_range = 6;
	}
}

void AccelMeter::setRad() {

	setG();

	_xRad = asin(_xG);
	_yRad = asin(_yG);
	_zRad = acos(_zG);
}

void AccelMeter::setG() {

	setRaw();

	_xG = calcG(_xRaw, 567, 1.395);
	_yG = calcG(_yRaw, 512);
	_zG = calcG(_zRaw);
}

void AccelMeter::setRaw() {
	
	_xRaw = analogRead(_xOut);
	_yRaw = analogRead(_yOut);
	_zRaw = analogRead(_zOut);
}


double AccelMeter::calcG(int raw, int offset, double scale) {

	int calibratedRaw = ((raw - offset) * scale);
	double g = calibratedRaw * _range / 1024 * 2;
		
	return g;
}
