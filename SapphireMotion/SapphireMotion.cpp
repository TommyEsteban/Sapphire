/*
  SapphireMotion.cpp - Library to control the motion of Sapphire vehicle based on two DC motors.
  Created by Tommy E. Garcia, November 26, 2015.
  Released as a part of the final project for CS50 course from Harvard University.
*/

#include "SapphireMotion.h"

SapphireMotion::SapphireMotion()
{
}

SapphireMotion::SapphireMotion(int digitalPinLeftMotor, int pwmPinLeftMotor, int digitalPinRightMotor, int pwmPinRightMotor)
{
	initialize(digitalPinLeftMotor, pwmPinLeftMotor, digitalPinRightMotor, pwmPinRightMotor);
}

void SapphireMotion::initialize(int digitalPinLeftMotor, int pwmPinLeftMotor, int digitalPinRightMotor, int pwmPinRightMotor)
{
	// set the left motor and right motor
	this->_left = new SapphireMotor(digitalPinLeftMotor, pwmPinLeftMotor);
	this->_right = new SapphireMotor(digitalPinRightMotor, pwmPinRightMotor);
	
	// initialize the compass
	Wire.begin();
	this->_compass.init();
	this->_compass.enableDefault();
	
	// set the min and max vectors for compass calibration
	this->_compass.m_min = (LSM303::vector<int16_t>){-4929, -2063, +10537};
	this->_compass.m_max = (LSM303::vector<int16_t>){-2515, +705, +13355};
}

void SapphireMotion::goForward(int speed)
{
	this->_left->moveForward(speed);
	this->_right->moveForward(speed);
}

void SapphireMotion::goForward(int speedLeft, int speedRight)
{
	this->_left->moveForward(speedLeft);
	this->_right->moveForward(speedRight);
}

void SapphireMotion::goBackward(int speed)
{
	this->_left->moveBackward(speed);
	this->_right->moveBackward(speed);
}

void SapphireMotion::goBackward(int speedLeft, int speedRight)
{
	this->_left->moveBackward(speedLeft);
	this->_right->moveBackward(speedRight);
}

void SapphireMotion::turnLeft(int speed)
{
	// to turn left, right motor goes to forward and left motor goes to backward
	this->_left->moveBackward(speed);
	this->_right->moveForward(speed);
}

void SapphireMotion::turnLeft(int speed, int angle)
{
	// variable to control some noise level of the compass readings
	int deltaNoise = 20;
	
	// this is the compass readings
	float currentTheta = 0;
	
	// this is difference between compass readings and first reading
	float deltaTheta = 0;

	// read the angle relative to the absolute north vector
	this->_compass.read();
	float initialTheta = this->_compass.heading((LSM303::vector<int>){0, 1, 0});

	// to turn left, right motor goes to forward and left motor goes to backward
	this->_left->moveBackward(speed);
	this->_right->moveForward(speed);
		
	while(true)
	{
		// read the current angle marked by the compass
		this->_compass.read();
		
		// the vector inside the heading function denotes the axis, 
		// we are interested in the Y axis since we need to control the angle perpendicular to the floor
		currentTheta = this->_compass.heading((LSM303::vector<int>){0, 1, 0});
		
		// compute the travelled angle
		if(currentTheta < initialTheta)
			deltaTheta = initialTheta - currentTheta;
		else
			deltaTheta = 360 - currentTheta + initialTheta;

		// when the travelled angle is between the given angle and a small span, the rotation has been completed
		if(deltaTheta > angle && deltaTheta < (angle + deltaNoise))
			break;
	}

	
	stop();
}

void SapphireMotion::turnRight(int speed)
{
	// to turn right, left motor goes to forward and right motor goes to backward
	this->_left->moveForward(speed);
	this->_right->moveBackward(speed);
}

void SapphireMotion::turnRight(int speed, int angle)
{
	// variable to control some noise level of the compass readings
	int deltaNoise = 20;
	
	// this is the compass readings
	float currentTheta = 0;
	
	// this is difference between compass readings and first reading
	float deltaTheta = 0;

	// read the angle relative to the absolute north vector
	this->_compass.read();
	float initialTheta = this->_compass.heading((LSM303::vector<int>){0, 1, 0});

	Serial.print("RIGHT initial: "); Serial.print(initialTheta);
	
	// to turn left, right motor goes to forward and left motor goes to backward
	this->_left->moveForward(speed);
	this->_right->moveBackward(speed);
		
	while(true)
	{
		// read the current angle marked by the compass
		this->_compass.read();
		
		// the vector inside the heading function denotes the axis, 
		// we are interested in the Y axis since we need to control the angle perpendicular to the floor
		currentTheta = this->_compass.heading((LSM303::vector<int>){0, 1, 0});
		
		// compute the travelled angle
		if(currentTheta > initialTheta)
			deltaTheta = currentTheta - initialTheta;
		else
			deltaTheta = 360 - initialTheta + currentTheta;

		// when the travelled angle is between the given angle and a small span, the rotation has been completed
		if(deltaTheta > angle && deltaTheta < (angle + deltaNoise))
			break;
	}
	
	stop();
}

void SapphireMotion::stop()
{
	// to stop the motion both motors must be stopped
	this->_left->stop();
	this->_right->stop();
}