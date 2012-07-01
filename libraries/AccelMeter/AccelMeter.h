#ifndef AccelMeter_h
#define AccelMeter_h

#include "Arduino.h"
#include "math.h"

#define G15 LOW
#define G60 HIGH

class AccelMeter {

	public:

	AccelMeter(
		int xOut, int yOut, int zOut, 
		int selfTest, int gSelect, int zgDetect, int nSleep
	);

	void setup(
		bool range=G15,
		int xLow=171, int xHigh=853,
		int yLow=171, int yHigh=853,
		int zLow=171, int zHigh=512
	);
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

	// calibration values
	int _xLow, _xHigh;
	int _yLow, _yHigh;
	int _zLow, _zHigh;
	
	// values
	int    _xRaw, _yRaw, _zRaw;
	double _xG,   _yG,   _zG;
	double _xRad, _yRad, _zRad;

	double _range;
	
	void   setRange(bool range=G15);
	void   setRaw();
};
#endif
