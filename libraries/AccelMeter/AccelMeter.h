#ifndef AccelMeter_h
#define AccelMeter_h

#include "Arduino.h"
#include "math.h"

#define _1_5G LOW
#define _6G   HIGH

class AccelMeter {

	public:

	AccelMeter(
		int xOut, int yOut, int zOut, bool range,
		int selfTest, int gSelect, int zgDetect, int nSleep
	);

	void setup();
	void sleep();
	void wake();
	
	void setG();	
	void setRad();	

	double xG();
	double yG();
	double zG();

	double xRad();
	double yRad();
	double zRad();

	bool zeroG();
	
	private:
	
	// IO Pins
	int _xOut, _yOut, _zOut;
	int _selfTest, _gSelect, _zgDetect, _nSleep;
	
	// values
	int    _xRaw, _yRaw, _zRaw;
	double _xG,   _yG,   _zG;
	double _xRad, _yRad, _zRad;

	double _range;
	
	void   setRange(bool range=_1_5G);
	void   setRaw();
	double calcG(int raw, int offset=512, double scale=1);
};
#endif
