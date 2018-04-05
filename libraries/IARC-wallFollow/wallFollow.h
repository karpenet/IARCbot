/*
 * wallFollow.h
 *
 *  Created on: 04-Mar-2018
 *      Author: karpenet
 */

#ifndef IARC_WALLFOLLOW_WALLFOLLOW_H_
#define IARC_WALLFOLLOW_WALLFOLLOW_H_

#include "motorControl.h"
#include <Arduino.h>
#include <lineFollow.h>

enum UltraSonic {leftSensor, frontSensor, rightSensor};

class wallFollow {
public:
	wallFollow();
	virtual ~wallFollow();

public:
	void initialize(int trig[3], int echo[3]);
	void sensorRead();
	int wallError(int dir);
	void contSpeed(int err);

	void leftFollow();
	void rightFollow();

	bool inFront();

public:

	motorControl wallMove;

	int leftspeed;
	int rightspeed;

	int trigPin[3];
	int echoPin[3];
	int duration[3];

};

#endif /* IARC_WALLFOLLOW_WALLFOLLOW_H_ */
