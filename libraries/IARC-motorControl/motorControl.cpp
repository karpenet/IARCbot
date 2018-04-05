/*
 * motorControl.cpp
 *
 *  Created on: 04-Mar-2018
 *      Author: karpenet
 */

#include "motorControl.h"

motorControl::motorControl() {
	// TODO Auto-generated constructor stub

}

motorControl::~motorControl() {
	// TODO Auto-generated destructor stub
}

void motorControl::initialize(){
	pinMode(PWM1A,OUTPUT);
	pinMode(PWM1B,OUTPUT);
	pinMode(PWM2A,OUTPUT);
	pinMode(PWM2B,OUTPUT);
}

//Non PID motion functions

void motorControl::stopMotion(){
	digitalWrite(PWM1A, LOW);
	digitalWrite(PWM1B, LOW);
	digitalWrite(PWM2A, LOW);
	digitalWrite(PWM2B, LOW);
}

void motorControl::moveSlow(){
	analogWrite(PWM1A, 100);
	analogWrite(PWM1B, MINSpeed);
    analogWrite(PWM2A, 100);
	analogWrite(PWM2B, MINSpeed);
}

void motorControl::moveForward(){
	analogWrite(PWM1A, WallSpeed);
	analogWrite(PWM1B, MINSpeed);
    analogWrite(PWM2A, WallSpeed);
	analogWrite(PWM2B, MINSpeed);
}

void motorControl::turnLeft(){
    analogWrite(PWM1A, 100);
    analogWrite(PWM1B, MINSpeed);
    analogWrite(PWM2A, WallSpeed);
    analogWrite(PWM2B, MINSpeed);
}

void motorControl::turnRight(){
	analogWrite(PWM1A, WallSpeed);
	analogWrite(PWM1B, MINSpeed);
	analogWrite(PWM2A, 100);
	analogWrite(PWM2B, MINSpeed);
}

void motorControl::turnLeftAround(){
	analogWrite(PWM1A, MINSpeed);
	analogWrite(PWM1B, WallSpeed);
	analogWrite(PWM2A, WallSpeed);
	analogWrite(PWM2B, MINSpeed);
}

void motorControl::turnRightAround(){
	analogWrite(PWM1A, WallSpeed);
	analogWrite(PWM1B, MINSpeed);
	analogWrite(PWM2A, MINSpeed);
	analogWrite(PWM2B, WallSpeed);
}

//Argument based motor control
void motorControl::argMove(int m1, int m2, int m3, int m4){

    analogWrite(PWM1A, m1);
    analogWrite(PWM1B, m2);
    analogWrite(PWM2A, m3);
    analogWrite(PWM2B, m4);

}

//PID motion functions

void motorControl::moveForwardPID(){
	analogWrite(PWM1A, leftSpeed);
	analogWrite(PWM1B, MINSpeed);
    analogWrite(PWM2A, rightSpeed);
    analogWrite(PWM2B, MINSpeed);
}

void motorControl::pidMove(int error){
	if (error > 0) {
	    leftSpeed = MAXSpeed - pidDiff;
	    rightSpeed = MAXSpeed + pidDiff;
	    speedMod();
	    analogWrite(PWM1A, leftSpeed);
	    analogWrite(PWM1B, MINSpeed);
	    analogWrite(PWM2A, rightSpeed);
	    analogWrite(PWM2B, MINSpeed);
	  }
	  else if (error==0){
	    leftSpeed=255;
	    rightSpeed=255;
	    analogWrite(PWM1A, leftSpeed);
	    analogWrite(PWM1B, MINSpeed);
	    analogWrite(PWM2A, rightSpeed);
	    analogWrite(PWM2B, MINSpeed);
	  }
	  else if (error < 0) {
	    leftSpeed = MAXSpeed + pidDiff;
	    rightSpeed = MAXSpeed - pidDiff;
	    speedMod();
	    analogWrite(PWM1A, leftSpeed);
	    analogWrite(PWM1B, MINSpeed);
	    analogWrite(PWM2A, rightSpeed);
	    analogWrite(PWM2B, MINSpeed);
	  }
}
void motorControl::pidController(int error){
	proportional = error;
	integral = integral + error;
	derivative = error - previousError;

	pidDiff = Kp*proportional + Ki*integral + Kd*derivative;

	previousError = error;
}

void motorControl::speedMod(){
    if(leftSpeed>255)
    	leftSpeed = 255;
    if(rightSpeed > 255)
    	rightSpeed = 255;
}
