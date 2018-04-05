/*
 * lineFollow.h
 *
 *  Created on: 04-Mar-2018
 *      Author: karpenet
 */

#ifndef IARC_LINEFOLLOW_LINEFOLLOW_H_
#define IARC_LINEFOLLOW_LINEFOLLOW_H_

#include <Arduino.h>
#include <motorControl.h>

#define speed1 	150
#define speed2	230


class lineFollow {
public:
	lineFollow();
	virtual ~lineFollow();

//Public member functions

public:
	void initialize(int frontPin[3], int arrayPin[5]);
	void irCalibration();

	void threeSensorRead();
	void fiveSensorRead();
	void frontSensorRead();
	int sensorRead();

	bool readMarker();
	bool readSection();

	char typeSection();

	int lineError(int sensor[5], int sensorFront[3]);

	void blackFollow();
	void whiteFollow();


//Public member variables

public:
	motorControl lineMove;

	int frontArray[3];
	int frontSense[3];

	int mainArray[5];
	int mainSense[5];

	int frontCmp = 0;
	int mainCmp = 0;

	int error;


	int lrFlag = 0;

	int dark;
	int light;
	int sensorValue;
	int PIDerror;

};

#endif /* IARC_LINEFOLLOW_LINEFOLLOW_H_ */
