/*
 * IARCbot.cpp
 *
 *  Created on: 09-Mar-2018
 *      Author: karpenet
 */

#include "IARCbot.h"

IARCbot::IARCbot() {
	// TODO Auto-generated constructor stub

}

IARCbot::~IARCbot() {
	// TODO Auto-generated destructor stub
}

void IARCbot::initialize(int fLine[3], int mLine[5], int tUltra[3], int eUltra[3],int fCol[4], int opCol, int bUsr[2],int lUsr){
	lineFollower.initialize(fLine, mLine);
	wallFollower.initialize(tUltra, eUltra);
	colorSense.initialize(fCol,opCol);
	botGUI.initialize(bUsr,lUsr);
	moveBot.initialize();
}

//Calibrates IR sensors
void IARCbot::calibration(){
	lineFollower.irCalibration();
}

void IARCbot::stop(){
	moveBot.stopMotion();
}

//Updates mode if marker is read
void IARCbot::modeUpdate(){
	if(lineFollower.readMarker()){
		botGUI.ledState(11,HIGH);

		if(mode == 5)
			mode = 0;
		else
			mode += 1;

		while(lineFollower.readMarker()){
			moveBot.moveSlow();
		}
		delay(500);
	}
	botGUI.dispCurrentMode(mode);
	botGUI.ledState(11,LOW);
}

//Detects debounced button press
bool IARCbot::buttonPressed(int inputButton){
	tactile = botGUI.buttonState(inputButton);
	return tactile;
}

void IARCbot::lineMode(){
	modeUpdate();
	lineFollower.blackFollow();
}

void IARCbot::wallMode(){

	modeUpdate();
	wallFollower.rightFollow();
}

void IARCbot::wallModeOpp(){

	modeUpdate();
	wallFollower.leftFollow();

}

void IARCbot::colorMode(){

	modeUpdate();
	colorSense.colorMotion();
}

void IARCbot::blinkyMode(){
	moveBot.stopMotion();
	botGUI.blinky(blinkyLED);
}
