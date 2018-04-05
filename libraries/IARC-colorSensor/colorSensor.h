/*
 * colorSensor.h
 *
 *  Created on: 05-Mar-2018
 *      Author: karpenet
 */



#ifndef LIBRARIES_IARC_COLORSENSOR_COLORSENSOR_H_
#define LIBRARIES_IARC_COLORSENSOR_COLORSENSOR_H_

#include <Arduino.h>
#include <wallFollow.h>
#include <motorControl.h>
#include <lineFollow.h>


class colorSensor {
public:
	colorSensor();
	virtual ~colorSensor();

public:
	void initialize(int sPin[4], int outPin);
	char colorRead();
	void colorMotion();
	void colorAlgo();

public:
	wallFollow followWall;
	lineFollow followLine;
	motorControl colorMove;

	int count = 0;

	int red, blue;
	int s[4], senseOut;
};

#endif /* LIBRARIES_IARC_COLORSENSOR_COLORSENSOR_H_ */
