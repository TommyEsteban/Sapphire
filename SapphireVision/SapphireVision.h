/*
  SapphireVision.h - Library to control the vision of Sapphire vehicle 
  based on one servo motor and one ultrasonic sensor.
  Created by Tommy E. Garcia, November 26, 2015.
  Released as a part of the final project for CS50 course from Harvard University.
*/

#ifndef SapphireVision_h
#define SapphireVision_h

#include "Arduino.h"
#include "NewPing.h"
#include "SapphireServo.h"

class SapphireVision
{
	public:
		
		// array to keep the readings of distances made by scan function
		unsigned int distances[180];
		
		// default constructor
		SapphireVision();
		
		// The first argument correspond to the pin to control the servo motor, 
		// the second argument is the type of the servo 360 degrees or 180 degrees, the third argument is the
		// echo pin of the ultrasonic sensor, the next argument is the trigger pin of the ultrasonic sensor
		// and the last parameter is the maximum distance range supported by the sensor
		void initialize(int servoPin, ServoType type, int echoPin, int triggerPin, int maxRange);
		
		// get the distance of the nearest object, returns -1 if the nearest object is beyond the limit of the sensor
		unsigned long getDistance();
		
		// get an average distance based on a number of lectures given by period parameter
		unsigned int getAverageDistance(int period);
		
		// set an offset for the frontal view, in case the frontal view does not match exactly in 90 degrees
		void setFrontalOffset(int value);
		
		// set the view to the front with a delay time
		void setToFront(int delayTime);
		
		// move the servo motor an angle between 0 and 180 with a delay time
		void move(int angle, int delayTime);
		
		// move the servo motor to the right with a delay time
		void moveRight(int delayTime);
		
		// move the servo motor to the left with a delay time
		void moveLeft(int delayTime);
		
		// scan 180 degrees and fills the array with the distances for every degree
		void scan();

	private:
		// the servo motor controller
		SapphireServo _servo;
		
		// type of the servo, 180 or 360 degrees
		ServoType _type;
		
		// the ultrasonic sensor controller
		NewPing *_sonar;
		
		// the pins used
		int _servoPin, _echoPin, _triggerPin, _maxRange;
		
		// In case the frontal view does not match exactly in 90 degrees, this variable keeps an offset value
		int _frontalOffset = 0;
		
		// To internally initialize the servo motor
		void initializeServo();
};

#endif