/*
 * lineFollow.cpp
 *
 *  Created on: 04-Mar-2018
 *      Author: karpenet
 */

#include "lineFollow.h"


#define delta 100

lineFollow::lineFollow() {
	// TODO Auto-generated constructor stub

}

lineFollow::~lineFollow() {
	// TODO Auto-generated destructor stub
}

void lineFollow::initialize(int frontPin[3], int arrayPin[5]){

	for(int i = 0; i<3; ++i){
		frontArray[i] = frontPin[i];
		pinMode(frontArray[i],INPUT);
	}

	for(int i = 0; i<5; ++i){
		mainArray[i] = arrayPin[i];
		pinMode(mainArray[i],INPUT);
	}

}


void lineFollow::frontSensorRead(){
	int tmp;
	for(int i = 0; i<3; ++i){

		tmp = analogRead(frontArray[i]);
		if(tmp >= 650){
			frontSense[i] = 1;
		}
		else if(tmp <= 600){  //light
			frontSense[i] = 0;
		}
	}
}

void lineFollow::fiveSensorRead(){
	int tmp;
	for(int i = 0; i<5; ++i){

		tmp = analogRead(mainArray[i]);
		if(tmp >= 270){
			mainSense[i] = 1;
		}
		else if(tmp <= 250){    //light
			mainSense[i] = 0;
		}
	}
}

//Determines error and orientation of robot if line overshot
int lineFollow::lineError(int sensorMain[5], int sensorFront[3]){


	if(sensorMain[0] == 0 && sensorMain[1]==1 && sensorMain[2]==1 && sensorMain[3]==1 && sensorMain[4] ==0)
		error = 0;
	else if(sensorMain[0]==0 && sensorMain[1]==1 && sensorMain[2]==1 && sensorMain[3]==0 && sensorMain[4] ==0)
		error = 1;
	else if(sensorMain[0]==0 && sensorMain[1]==0 && sensorMain[2]==1 && sensorMain[3]==1 && sensorMain[4] ==0)
		error = -1;
	else if(sensorMain[0]==1 && sensorMain[1]==1 && sensorMain[2]==0 && sensorMain[3]==0 && sensorMain[4] ==0)
		error = 2;
	else if(sensorMain[0]==0 && sensorMain[1]==0 && sensorMain[2]==0 && sensorMain[3]==1 && sensorMain[4] ==1)
		error = -2;
	else if(sensorMain[0]==1 && sensorMain[4] ==0){
		error = 3;
		lrFlag = 0;
	}
	else if(sensorMain[0]==0 && sensorMain[4] ==1){
		error = -3;
		lrFlag = 1;
	}
	else if(sensorMain[0]==1 && sensorMain[1]==1 && sensorMain[2]==1 && sensorMain[3]==1 && sensorMain[4] ==1){
		error = 4;
		lrFlag = 1;
	}
	else if(sensorMain[0] == 0 && (sensorMain[1] == 1 || sensorMain[1] == 0) && sensorMain[2] == 1 && sensorMain[3] == 1 && sensorMain[4] == 1 && sensorFront[1] == 1)
		error = 0;
	else if(sensorMain[0] == 1  && sensorMain[1] == 0 && sensorMain[2] == 0 && sensorMain[3] == 0 && sensorMain[4] == 1)
		error = 5;
	else if(sensorMain[0] == 0  && sensorMain[1] == 1 && sensorMain[2] == 0 && (sensorMain[3] == 1 || sensorMain[3] == 0) && sensorMain[4] == 1)
		error = 6;
	else if(sensorMain[0] == 0  && sensorMain[1] == 0 && sensorMain[2] == 0 && sensorMain[3] == 0 && sensorMain[4] == 0)
		error = 7;

	return error;

}


void lineFollow::blackFollow(){
	fiveSensorRead();
	frontSensorRead();
	PIDerror = lineError(mainSense,frontSense);
	if(PIDerror<4 && PIDerror>-4)
	{
		lineMove.pidController(PIDerror);
		lineMove.pidMove(PIDerror);
	}

	else if (PIDerror == 4) {
		lineMove.argMove(150,0,150,0);
		delay(100);
		lineMove.argMove(0,150,150,0);
		delay(500); //check
	  }
	else if (PIDerror == 5) {
		lineMove.argMove(150,0,230,0);
	  }
	else if (PIDerror == 6) {
		lineMove.argMove(150,0,230,0);
	  }
	else if (PIDerror == 7) {
		if (lrFlag == 0) {
			lineMove.argMove(0,150,150,0);
	    }
	    else if (lrFlag == 1) {
	    	lineMove.argMove(150,0,0,150);
	    }

	  }
}

//Reads mode change markers
bool lineFollow::readMarker(){
	frontCmp =0;
	mainCmp =0;

	fiveSensorRead();
	frontSensorRead();

	for(int i = 0; i<3; ++i){
		if(frontSense[i]==1)
			frontCmp += 1;
		else
			frontCmp += 0;
	}

	for(int i = 0; i<5; ++i){
		if(mainSense[i]==1)
			mainCmp += 1;
		else
			mainCmp += 0;
	}

	if(frontCmp == 3 && mainCmp == 5)
		return true;
	else
		return false;
}

//Determines if intersection is reached
bool lineFollow::readSection(){
	fiveSensorRead();

	if((mainSense[0] == 1 && mainSense[1] == 1 && mainSense[2] == 1) || (mainSense[2] == 1 && mainSense[3] == 1 && mainSense[4] == 1))
		return 1;
	else
		return 0;
}

//Reads direction of intersection
char lineFollow::typeSection(){
	fiveSensorRead();

	if(mainSense[0] == 1 && mainSense[1] == 1 && mainSense[2] == 1)
		return "L";
	if(mainSense[2] == 1 && mainSense[3] == 1 && mainSense[4] == 1)
		return "R";
}
