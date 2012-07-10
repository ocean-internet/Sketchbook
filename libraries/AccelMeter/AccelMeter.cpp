#include <AccelMeter.h>

// kP = 2550 - full power @ +/-5 degrees
AccelMeter::AccelMeter(
	int xOut, int yOut, int zOut, 
	int selfTest, int gSelect, int zgDetect, int nSleep  
) {

	_xOut     = xOut;
	//_yOut     = yOut;
	_zOut     = zOut;

	_selfTest = selfTest;
	_gSelect  = gSelect;
	_zgDetect = zgDetect;
	_nSleep   = nSleep;
}

void AccelMeter::setup(bool range, int xLow, int xHigh, int yLow, int yHigh, int zLow, int zHigh) {

	setRange(range);

	_xLow = xLow;
	//_yLow = yLow;
	_zLow = zLow;

	_xHigh = xHigh;
	//_yHigh = yHigh;
	_zHigh = zHigh;

	pinMode(_selfTest, OUTPUT);
	pinMode(_gSelect,  OUTPUT);
	pinMode(_zgDetect, OUTPUT);
	pinMode(_nSleep,   OUTPUT);
}

void AccelMeter::sleep() {

	digitalWrite(_nSleep, LOW);
}

void AccelMeter::wake() {
	
	digitalWrite(_nSleep,   HIGH);
	digitalWrite(_selfTest, LOW);
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
}

void AccelMeter::setRad() {

	setG();

	double ninteyDegrees = 1.57079633;

	if(_xG >= 1) {
		_xRad = ninteyDegrees;
	} else if(_xG <= -1) {
		_xRad = -(ninteyDegrees);	
	} else {
		_xRad = asin(_xG);
	}

	/*
	if(_yG >= 1) {
		_yRad = ninteyDegrees;
	} else if(_yG <= -1) {
		_yRad = -(ninteyDegrees);
	} else {
		_yRad = asin(_yG);	
	}
	*/
	
	_zRad = acos(_zG);
}

void AccelMeter::setG() {

	setRaw();

	_xG = ((double) map(_xRaw, _xLow, _xHigh, -1024, 1024)) / 1024;
	//_yG = ((double) map(_yRaw, _yLow, _yHigh, -1024, 1024)) / 1024;
	_zG = ((double) map(_zRaw, _zLow, _zHigh, -1024, 1024)) / 1024;
}

void AccelMeter::setRaw() {
	
	_xRaw = analogRead(_xOut);
	//_yRaw = analogRead(_yOut);
	_zRaw = analogRead(_zOut);
}
