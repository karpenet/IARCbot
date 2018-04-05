/*
 * motorControl.h
 *
 *  Created on: 04-Mar-2018
 *      Author: karpenet
 */

#ifndef LIBRARIES_IARC_MOTORCONTROL_MOTORCONTROL_H_
#define LIBRARIES_IARC_MOTORCONTROL_MOTORCONTROL_H_

#include <Arduino.h>

#define MAXSpeed 200
#define MINSpeed 0
#define WallSpeed 230

#define Kp 10
#define Ki 0
#define Kd 25

#define PWM1A 2
#define PWM1B 3
#define PWM2A 4
#define PWM2B 5

class motorControl {
public:
	motorControl();
	virtual ~motorControl();

public:
	void initialize();
	void stopMotion();

	void moveSlow();
	void turnLeft();
	void turnRight();
	void moveForward();
	void moveBackward();
	void turnLeftAround();
	void turnRightAround();
	void argMove(int m1, int m2, int m3, int m4);

	void turnLeftPID();
	void turnRightPID();
	void moveForwardPID();
	void moveBackwardPID();
	void turnLeftAroundPID();
	void turnRightAroundPID();

	void pidController(int error);
	void pidMove(int error);

	void speedMod();

public:
	int begin;
	int error, previousError;
	int proportional, integral, derivative;
	int pidDiff;
	int leftSpeed, rightSpeed;

};

#endif /* LIBRARIES_IARC_MOTORCONTROL_MOTORCONTROL_H_ */
