/*
  SapphireController.cpp - This is the main controller for the Sapphire vehicle 
  Created by Tommy E. Garcia, November 26, 2015.
  Released as a part of the final project for CS50 course from Harvard University.
*/

#include "SapphireController.h"

// this is the global speed to move the motors
#define SPEED 70

// the minimum distance to which is considered an obstacle
#define MIN_OBSTACLE_DISTANCE 15

// time delay after the position of the vision is set to front
#define VISION_DELAY 200

// variable to calibrate the position of the vision sensor 
#define VISION_OFFSET -5

// this is the speed of the serial ports in bauds per second
#define SERIAL_SPEED 9600

// maximum angle of the vision system
#define MAX_ANGLE 180

// variable to control the initialization of the serial ports
bool serialInitialized = false;

// this is the speed of the right motor
int speedRight = SPEED;

// this is the speed of the left motor 
// (this motor for some reason it is weakest than the right one.)
int speedLeft = SPEED + 20;

// continuous distance readings
unsigned int distance = 0;

SapphireController::SapphireController(int leadPin)
{
	this->_leadPin = leadPin;
	
	// set the led pin as an output
	pinMode(this->_leadPin, OUTPUT);
}

void SapphireController::initializeMotion(int digitalPinLeftMotor, int pwmPinLeftMotor, int digitalPinRightMotor, int pwmPinRightMotor)
{
	// check for initialization of the serial ports in the arduino
	if(!serialInitialized)
	{
		Serial.begin(SERIAL_SPEED);
		serialInitialized = true;
	}
	
	// initialize the pins of the motion system
	this->_motion.initialize(digitalPinLeftMotor, pwmPinLeftMotor, digitalPinRightMotor, pwmPinRightMotor);
	
	// put the pins of the motion system in LOW
	this->_motion.stop();
}

void SapphireController::initializeVision(int servoPin, ServoType type, int echoPin, int triggerPin, int maxRange)
{
	// check for initialization of the serial ports in the arduino
	if(!serialInitialized)
	{
		Serial.begin(SERIAL_SPEED);
		serialInitialized = true;
	}
	
	// initialize the pins of the vision system
	this->_vision.initialize(servoPin, type, echoPin, triggerPin, maxRange);
	
	// calibrate the position and set the vision to the front
	this->_vision.setFrontalOffset(VISION_OFFSET);
	this->_vision.setToFront(VISION_DELAY);
}

void SapphireController::runAutonomousMode()
{
	// stop the vehicle and scan distances
	this->_motion.stop();
	this->_vision.scan();
	
	// after collecting distances make a decision about what direction the vehicle must go
	Decision d = makeDecision(this->_vision.distances);
	
	// restore the vision to the front
	this->_vision.setToFront(VISION_DELAY);
	
	//depending of the decision result, proceed in the given direction
	if(d.direction == LEFT)
	{
		// blink the led five times with a delay of 200 milliseconds every time.
		blinkLed(5, 200);
		
		//turn left 90 degrees
		this->_motion.turnLeft(SPEED, 90);
		
		// change the direction to forward
		d.direction = FORWARD;
	}
	
	if(d.direction == RIGHT)
	{
		// blink the led ten times with a delay of 200 milliseconds every time.
		blinkLed(10, 200);
		
		//turn right 90 degrees
		this->_motion.turnRight(SPEED, 90);
		
		// change the direction to forward
		d.direction = FORWARD;
	}
	
	if(d.direction == BACKWARD)
	{
		//turn left 180 degrees
		this->_motion.turnLeft(SPEED, MAX_ANGLE);
		
		// change the direction to forward
		d.direction = FORWARD;
	}
	
	// after turning left/right or if the decision is go forward proceed
	if(d.direction == FORWARD)
	{
		//Serial.print("FORWARD: "); Serial.println(d.nearest);
		this->_motion.goForward(speedLeft, speedRight);
		
		// after starting move forward, check the distance continuously until obstacle is detected
		distance = this->_vision.getAverageDistance(3);
		while(distance == 0 || distance > MIN_OBSTACLE_DISTANCE)
			distance = this->_vision.getAverageDistance(3);
	}
}

Decision SapphireController::makeDecision(unsigned int readings[])
{
	// the variable to return the decision result
	Decision d;
	
	// indexes to split the vision range
	int rIndex = 0, fIndex = 61, lIndex = 121;
	
	// variables to compute the minimum distance in every direction
	int minRight = 7777, minFront = 7777, minLeft = 7777;
	
	// variables to keep the angles
	int minRightIndex = rIndex, minFrontIndex = fIndex, minLeftIndex = lIndex;
	
	// scan distances from 0 to 180 degrees and compute the minimum distance for every zone of 60 degrees
	for(int i = 0; i <= MAX_ANGLE; i++)
	{
		// this is the right zone, it goes from 0 to 60 degrees
		if(i > 0 && i < fIndex)
		{
			if(readings[i] > 0 && readings[i] < minRight)
			{
				minRight = readings[i];
				minRightIndex = i;
			}
		}
		
		// this is the front zone, it goes from 61 to 120 degrees, 
		if(i > 60 && i < lIndex)
		{
			if(readings[i] > 0 && readings[i] < minFront)
			{
				minFront = readings[i];
				minFrontIndex = i;
			}
		}
		
		// this is the right zone, it goes from 121 to 180 degrees
		if(i > 120 && i <= MAX_ANGLE)
		{
			if(readings[i] > 0 && readings[i] < minLeft)
			{
				minLeft = readings[i];
				minLeftIndex = i;
			}
		}
	}
	
	// if the minimum distance in the front zone is largest than the threshold, go in this direction
	if(minFront > MIN_OBSTACLE_DISTANCE)
	{
		d.direction = FORWARD;
		d.nearest = minFront;
	}
	
	// if the minimum distance in the right zone is largest than the threshold, go in this direction
	else if(minRight > MIN_OBSTACLE_DISTANCE && minRight >= minLeft)
	{
		d.direction = RIGHT;
		d.nearest = minRight;
	}
	
	// if the minimum distance in the left zone is largest than the threshold, go in this direction
	else if(minLeft > MIN_OBSTACLE_DISTANCE && minLeft >= minRight)
	{
		d.direction = LEFT;
		d.nearest = minLeft;
	}
	
	// if there is no option in the zones, get back 
	else
	{
		d.direction = BACKWARD;
		d.nearest = -1;
	}
	
	return d;
}

void SapphireController::blinkLed(int counter, int time)
{
	// turn the led on and off
	for(int i = 0; i < counter; i++)
	{
		digitalWrite(this->_leadPin, HIGH);
		delay(time);
		digitalWrite(this->_leadPin, HIGH);
	}
	
	// turn the led off
	digitalWrite(this->_leadPin, LOW);
}
