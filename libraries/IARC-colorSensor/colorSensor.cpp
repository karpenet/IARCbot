/*
 * colorSensor.cpp
 *
 *  Created on: 05-Mar-2018
 *      Author: karpenet
 */

#include "colorSensor.h"

colorSensor::colorSensor() {
	// TODO Auto-generated constructor stub

}

colorSensor::~colorSensor() {
	// TODO Auto-generated destructor stub
}

void colorSensor::initialize(int sPin[4], int outPin){
	pinMode(sPin[0],OUTPUT);
	pinMode(sPin[1],OUTPUT);
	pinMode(sPin[2],OUTPUT);
	pinMode(sPin[3],OUTPUT);

	pinMode(outPin,INPUT);
}

//Reads red and blue color frequencies
char colorSensor::colorRead(){
	digitalWrite(s[0], HIGH);
	digitalWrite(s[1], LOW);
	digitalWrite(s[2], LOW);
	digitalWrite(s[3], LOW);
	red = pulseIn(senseOut, LOW); // Reading RED component of color

	digitalWrite(s[0], HIGH);
	digitalWrite(s[1], LOW);
	digitalWrite(s[2], LOW);
	digitalWrite(s[3], HIGH);
	blue = pulseIn(senseOut, LOW);

	if(blue>red)
		return "R";
	if(blue<red)
		return "B";
}

//Detects color, moves right if Red, left if Blue
void colorSensor::colorAlgo(){
	char color;

	colorMove.stopMotion();
	color = colorRead();

	if(color == "R")
		colorMove.argMove(100,0,0,100);
	if(color == "B")
		colorMove.argMove(0,100,100,0);
}

//Follows black line until block is detected
void colorSensor::colorMotion(){

	while(!followLine.readSection()){
		followLine.blackFollow();
	}

	if(followLine.typeSection() == "L"){
		if(followWall.inFront()){
			colorAlgo();
			delay(500);
			count += 1;
		}
		else
			colorMove.argMove(0,100,100,0);
	}

	if(followLine.typeSection() == "R"){
		if(followWall.inFront()){
			colorAlgo();
			delay(500);
			count += 1;

		}
		else
			colorMove.argMove(100,0,0,100);
	}

}
