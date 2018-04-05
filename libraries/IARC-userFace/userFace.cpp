/*
 * userFace.cpp
 *
 *  Created on: 09-Mar-2018
 *      Author: karpenet
 */

#include "userFace.h"

userFace::userFace(){}

userFace::~userFace(){
	// TODO Auto-generated destructor stub
}

void userFace::initialize(int buttonPin[2], int ledPin){
	pinMode(buttonPin[0],INPUT);
	pinMode(buttonPin[1],INPUT);
	pinMode(ledPin,OUTPUT);

	lcdDisp.begin(SSD1306_SWITCHCAPVCC, 0x3C);

	lcdDisp.display();
	lcdDisp.clearDisplay();

}

void userFace::dispCurrentMode(int botCurrentMode){

	lcdDisp.setTextSize(1);
	lcdDisp.setTextColor(WHITE);
	lcdDisp.setCursor(0,0);
	lcdDisp.println("Beeclust-MRSL");

	lcdDisp.setCursor(0,10);
	lcdDisp.print("Mode: ");
	lcdDisp.print(botCurrentMode);

	lcdDisp.setCursor(0,20);
	lcdDisp.print("Count: ");
	lcdDisp.print(block.count);

	lcdDisp.display();
	lcdDisp.clearDisplay();

}


void userFace::blinky(int pin){
	digitalWrite(pin, HIGH);
	delay(1000);
	digitalWrite(pin, LOW);
	delay(1000);
}

void userFace::ledState(int pin, int state){
	digitalWrite(pin, state);
}


bool userFace::buttonState(int tactButton){
	  int reading = digitalRead(tactButton);

	  if (reading != lastButtonState) {
	    lastDebounceTime = millis();
	  }

	  if ((millis() - lastDebounceTime) > debounceDelay) {
	    if (reading != bstate) {
	      bstate = reading;
	    }
	  }
	  lastButtonState = reading;

	  return bstate;
}

