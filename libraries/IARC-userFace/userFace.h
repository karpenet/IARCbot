/*
 * userFace.h
 *
 *  Created on: 09-Mar-2018
 *      Author: karpenet
 */

#ifndef IARC_USERFACE_USERFACE_H_
#define IARC_USERFACE_USERFACE_H_

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Arduino.h>

#include <colorSensor.h>

#define SSD1306_LCDHEIGHT  64




class userFace {
public:
	userFace();
	virtual ~userFace();

public:
	void initialize(int buttonPin[2], int ledPin);
	void dispCurrentMode(int botCurrentMode);
	void senseCalib(int dark, int light);
	void senseCalib(int readingIR);
	void dispClear();
	void blinky(int pin);
	void ledState(int pin, int state);

	bool buttonState(int tactButton);

public:

	Adafruit_SSD1306 lcdDisp;
	colorSensor block;

	char currMode;

	int bstate;
	int lastButtonState = LOW;

	unsigned long lastDebounceTime = 0;
	unsigned long debounceDelay = 50;



};

#endif /* IARC_USERFACE_USERFACE_H_ */

