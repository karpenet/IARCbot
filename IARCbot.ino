#include <Arduino.h>

#include <IARCbot.h>
#include <userFace.h>

//Pin Description

//Infrared Array (front - 3 sensor and main - 5 sensor)
int fSensor[3] = {A8,A9,A10};
int mSensor[5] = {A1,A2,A3,A4,A5};

//Ultrasonic Sensors
int trig[3] = {22,24,26};
int echo[3] = {6,7,8};

//TCS3200 Color Sensor
int filter[4] = {36,34,32,30};
int outputEn = 9;

//Tactile Buttons and LEDs
int button[2] = {A11,A12};
int LED = 10;

//Flag variables
int state = 1;
int count = 0;


IARCbot blineBot;
userFace GUI;


void setup()
{
	Serial.begin(9600);
	blineBot.mode=0;
	blineBot.initialize(fSensor, mSensor, trig, echo, filter, outputEn, button,LED);

	//Stop motion after initialization
	blineBot.stop();
	delay(2000);
/*	while(1){
		GUI.blinky(LED);
		state = blineBot.buttonPressed(button[0]);
		count =count + 1;
		if(count>5 && state == 0){
			return;
		}
	}
*/

}


void loop()
{

	if(blineBot.mode == 0){
		blineBot.stop();
		blineBot.modeUpdate();
	}
	else if(blineBot.mode == 1)
		blineBot.lineMode();

	else if(blineBot.mode == 2)
		blineBot.wallMode();

	else if(blineBot.mode == 3)
		blineBot.wallModeOpp();

	else if(blineBot.mode == 4)
		blineBot.colorMode();

	else if(blineBot.mode == 5)
		blineBot.blinkyMode();

}
