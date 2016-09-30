/*
  SapphireController.h - This is the main controller for the Sapphire vehicle 
  Created by Tommy E. Garcia, November 26, 2015.
  Released as a part of the final project for CS50 course from Harvard University.
*/

#ifndef SapphireController_h
#define SapphireController_h

#include "Arduino.h"
#include "SapphireMotion.h"
#include "SapphireVision.h"

enum Directions {FORWARD, LEFT, RIGHT, BACKWARD};

// this structure keeps the decision of the vehicle, it provides
// the direction which it must go and the distance of the nearest object.
typedef struct 
{
	Directions direction;
	int nearest;
}Decision;

class SapphireController
{
	public:
		
		// default constructor
		SapphireController(int leadPin);
		
		// initialize the motion system
		void initializeMotion(int digitalPinLeftMotor, int pwmPinLeftMotor, int digitalPinRightMotor, int pwmPinRightMotor);
		
		// initialize the vision system
		void initializeVision(int servoPin, ServoType type, int echoPin, int triggerPin, int maxRange);
		
		// run the autonomous mode
		void runAutonomousMode();
		
		// make blink the lead pin a number of times a given time per iteration
		void blinkLed(int counter, int time);

	private:
		// the motion system
		SapphireMotion _motion;
		
		// the vision system
		SapphireVision _vision;
		
		// lead pin number
		int _leadPin;
		
		// function to compute the decision to go ahead, turn right or turn left
		Decision makeDecision(unsigned int readings[]);
};

#endif