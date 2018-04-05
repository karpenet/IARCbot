/*
 * wallFollow.cpp
 *
 *  Created on: 04-Mar-2018
 *      Author: karpenet
 */

#include "wallFollow.h"

wallFollow::wallFollow() {
	// TODO Auto-generated constructor stub

}

wallFollow::~wallFollow() {
	// TODO Auto-generated destructor stub
}

void wallFollow::initialize(int trig[3], int echo[3]){
	for(int i = 0; i<3; ++i){
		trigPin[i] = trig[i];
		echoPin[i]  = echo[i];

		pinMode(trigPin[i],OUTPUT);
		pinMode(echoPin[i],INPUT);
	}

}

void wallFollow::sensorRead(){

	digitalWrite(trigPin[leftSensor], LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin[leftSensor], HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin[leftSensor], LOW);

	duration[leftSensor] = pulseIn(echoPin[leftSensor], HIGH);
	digitalWrite(trigPin[frontSensor], LOW);
	delayMicroseconds(2);
	digitalWrite(trigPin[frontSensor], HIGH);
	delayMicroseconds(10);
    digitalWrite(trigPin[frontSensor], LOW);

    duration[frontSensor] = pulseIn(echoPin[frontSensor], HIGH);


    digitalWrite(trigPin[rightSensor], LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin[rightSensor], HIGH);
    delayMicroseconds(10);
	digitalWrite(trigPin[rightSensor], LOW);

    duration[rightSensor] = pulseIn(echoPin[rightSensor], HIGH);
}

//Determines error in distance of the wall
int wallFollow::wallError(int dir){

	int error;

	if(duration[1] > 700 && duration[dir] <= 600 && duration[dir] > 550)
	    error=0;
	else if(duration[1]>700 && duration[dir]<=550 && duration[dir]>400)
	    error=-1;
	else if(duration[1]>700 && duration[dir]<=400 && duration[dir]>250)
	    error=-2;
	else if(duration[1]>700 && duration[dir]<=250 && duration[dir]>100)
	    error=-3;
	else if(duration[1]>700 && duration[dir]<=750 && duration[dir]>600)
	    error=1;
	else if(duration[1]>700 && duration[dir]<=900 && duration[dir]>750)
	    error=2;
	else if(duration[1]>700 && duration[dir]<=1050 && duration[dir]>900)
	    error=3;

	return error;
}

//Calculates PID speeds
void wallFollow::contSpeed(int err){
	  int PID = 10*err;

	  leftspeed= 180 - PID;
	  rightspeed= 180 + PID;
}

void wallFollow::leftFollow(){

	sensorRead();
	int werr = wallError(0);
	contSpeed(werr);

	if(duration[leftSensor] < 1050 && duration[frontSensor]>700)
		wallMove.argMove(leftspeed,0,rightspeed,0);
	else if (duration[leftSensor]>1000 && duration[frontSensor]>700)
		{
		wallMove.argMove(70,0,150,0);
	    delay(650); //check
		}
	else if (duration[leftSensor] <= 1000 && duration[frontSensor] <= 700){
		wallMove.argMove(150,0,0,0);
		delay(650); //check
	}




}

void wallFollow::rightFollow(){
	sensorRead();
	int werr = wallError(2);
	contSpeed(werr);

	if (duration[rightSensor] <= 1050 && duration[frontSensor] > 700)
		wallMove.argMove(rightspeed,0,leftspeed,0);
	else if (duration[rightSensor]>1000 && duration[frontSensor]>700)
		{
		wallMove.argMove(150,0,70,0);
	    delay(650); //check
		}
	else if (duration[rightSensor] <= 1000 && duration[frontSensor] <= 700){
		wallMove.argMove(0,0,150,0);
		delay(650); //check
	}


}

//Determines if there is a wall in front
bool wallFollow::inFront(){
	sensorRead();
	if(duration[frontSensor] <= 1000)
		return true;
	else
		return false;
}
