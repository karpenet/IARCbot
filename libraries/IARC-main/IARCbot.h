/*
 * IARCbot.h
 *
 *  Created on: 09-Mar-2018
 *      Author: karpenet
 */

#ifndef IARC_MAIN_IARCBOT_H_
#define IARC_MAIN_IARCBOT_H_

#define blinkyLED 10

#include <lineFollow.h>
#include <wallFollow.h>
#include <colorSensor.h>
#include <userFace.h>

class IARCbot {
public:
	IARCbot();
	virtual ~IARCbot();

public:
	void initialize(int fLine[3], int mLine[5], int tUltra[3], int eUltra[3],int fCol[4], int opCol, int bUsr[2],int lUsr);

	bool buttonPressed(int inputButton);
	void modeUpdate();
	void dispMode();

	void calibration();
	void stop();

	//IARC modes
	void lineMode();
	void wallMode();
	void wallModeOpp();
	void colorMode();
	void blinkyMode();

public:
	lineFollow lineFollower;
	wallFollow wallFollower;
	colorSensor colorSense;
	motorControl moveBot;
	userFace botGUI;

	int flag = 2;
	int mode;
	int tactile;

	char next;
};

#endif /* IARC_MAIN_IARCBOT_H_ */
