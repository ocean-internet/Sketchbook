/*
 * File:   KalmanFilter.h
 * Author: Andy Weir
 *
 * Description: My interpretation of a Kalman(esque) filter for balancing robot.
 * Created on 02 July 2012, 22:06
 */

#ifndef KALMANFILTER_H
#define	KALMANFILTER_H

class KalmanFilter {

	public:
		KalmanFilter(int weight=10, int timeStep=10000);
		void   init();
		double angle(double acelAngle=0, double gyroRate=0);

	private:

		int _weight;   // weighting given to old averages - (_weight - 1) : 1
		int _timeStep; // in microseconds

		double _aveAcelAngle; // in radians
		double _aveCalcAngle; // in radians

		double _acelAngle; // in radians
		double _gyroRate;  // in radians / millisecond
		double _gyroAngle; // in radians
		double _calcAngle; // in radians

		void _setAveAcelAngle(); // set the average accelerometer angle in radians
		void _setAveCalcAngle(); // set the average calculated angle in radians

		void _setGyroAngle(); // set the gyroscope angle in radians
		void _setCalcAngle(); // set the calculated angle in radians

		double _angleError(); // returns the difference between the calculated angle and the measured (accelerometer) angle
};

#endif	/* KALMANFILTER_H */

