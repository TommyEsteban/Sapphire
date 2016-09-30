/*
  SapphireVision.cpp - Library to control the vision of Sapphire vehicle 
  based on one servo motor and one ultrasonic sensor.
  Created by Tommy E. Garcia, November 26, 2015.
  Released as a part of the final project for CS50 course from Harvard University.
*/

#include "SapphireVision.h"

// maximum range of distance supported by the sensor
#define MAXRANGE 400

// front position angle
#define FRONT 90

// right position angle
#define RIGHT 0

// left position angle
#define LEFT 180

// period to take average distances
#define PERIOD 3

// maximum angle for scanning
#define MAX_ANGLE 180

SapphireVision::SapphireVision()
{
}

void SapphireVision::initialize(int servoPin, ServoType type, int echoPin, int triggerPin, int maxRange)
{
	// set the pins used
	this->_servoPin = servoPin;
	this->_type = type;
	this->_echoPin = echoPin;
	this->_triggerPin = triggerPin;
	this->_maxRange = maxRange;
	
	// initialize the ultrasonic sensor
	this->_sonar = new NewPing(this->_triggerPin, this->_echoPin, this->_maxRange);
}

void SapphireVision::initializeServo()
{
	// control if the servo is initialized
	if(!this->_servo.isInitialized)
		this->_servo.initialize(this->_servoPin, SERVO180);       
}

unsigned long SapphireVision::getDistance()
{
	// the returned distances are in centimeters
	return this->_sonar->ping_cm();
}

unsigned int SapphireVision::getAverageDistance(int period)
{
	// get the median time of a given number of ultrasonic signals
	unsigned long medianTime = this->_sonar->ping_median(period);
	
	// convert the microseconds to centimeters
	return this->_sonar->convert_cm(medianTime);
}

void SapphireVision::setFrontalOffset(int value)
{
	this->_frontalOffset = value;
}

void SapphireVision::setToFront(int delayTime)
{
	// initialize the servo motor, set the position to 90 degrees and wait a little bit 
	initializeServo();
	this->_servo.setPosition(FRONT + this->_frontalOffset);
    delay(delayTime);
}

void SapphireVision::move(int angle, int delayTime)
{
	// initialize the servo motor, set the position to the given angle and wait a little bit 
	initializeServo();
	this->_servo.setPosition(angle);
    delay(delayTime);         
}

void SapphireVision::moveRight(int delayTime)
{
	// initialize the servo motor, set the position to the right and wait a little bit 
	initializeServo();
	this->_servo.setPosition(RIGHT);
    delay(delayTime);         
}

void SapphireVision::moveLeft(int delayTime)
{
	// initialize the servo motor, set the position to the left and wait a little bit 
	initializeServo();
	this->_servo.setPosition(LEFT);
    delay(delayTime);         
}

void SapphireVision::scan()
{
	// set the initial position of the vision system to 0 degrees
	move(0, 200);
	
	// go from 0 to the maximum angle for scanning and read an average distance every degree
	for(int i = 0; i <= MAX_ANGLE; i++)
	{
		move(i, 0);
		distances[i] = getAverageDistance(PERIOD);
	}
}


