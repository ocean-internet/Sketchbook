/*
 * File:   KalmanFilter.cpp
 * Author: goofys
 *
 * Created on 02 July 2012, 22:06
 */

#include "KalmanFilter.h"

KalmanFilter::KalmanFilter(int weight, int timeStep) {

	_weight   = weight;
	_timeStep = timeStep;
}

void KalmanFilter::init() {

	_aveAcelAngle = 0;
	_aveCalcAngle = 0;

	_acelAngle = 0;
	_gyroRate  = 0;
	_gyroAngle = 0;
	_calcAngle = 0;
}

double KalmanFilter::angle(double acelAngle, double gyroRate) {

	_acelAngle = acelAngle;
	_gyroRate  = gyroRate;
	_setGyroAngle();
	_setAveAcelAngle();
	_setAveCalcAngle();
	_setCalcAngle();

	return _calcAngle;
}

/**
 * Description: sets average accelerometer angle in radians
 *
 * if _weight = 10;
 * _aveAcelAngle = 0.9 * _aveAcelAngle + 0.1 * newAcelAngle;
 *
 * @param newAcelAngle angle in radians
 */
void KalmanFilter::_setAveAcelAngle() {

	double oldAcelAngle;
	double newAcelAngle;

	oldAcelAngle = _aveAcelAngle / _weight * (_weight - 1);
	newAcelAngle = _acelAngle    / _weight * 1;

	_aveAcelAngle = oldAcelAngle + newAcelAngle;
}

/**
 * Description: sets average gyro angle in radians
 *
 * if _weight    = 10;
 * _aveGyroAngle = 0.9 * _aveGyroAngle + 0.1 * newGyroAngle;
 *
 * @param newGyroAngle angle in radians
 */
void KalmanFilter::_setAveCalcAngle() {

	double oldCalcAngle;
	double newCalcAngle;

	oldCalcAngle = _aveCalcAngle / _weight * (_weight - 1);
	newCalcAngle = _gyroAngle    / _weight * 1;

	_aveCalcAngle = oldCalcAngle + newCalcAngle;
}

double KalmanFilter::_angleError() {

	return _aveAcelAngle - _aveCalcAngle;
}

/**
 *
 * @param gyroRate in radians / millisecond
 * @return double gyroAngle in radians
 */
void KalmanFilter::_setGyroAngle() {

	_gyroAngle = (_gyroRate * _timeStep / 1000) + _calcAngle;
}

void KalmanFilter::_setCalcAngle() {

	_calcAngle = _calcAngle + _angleError() + _gyroAngle;
}
