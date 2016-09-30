/*
  SapphireMotor.cpp - Library to control one DC motor based on H-Bridge.
  Created by Tommy E. Garcia, November 26, 2015.
  Released as a part of the final project for CS50 course from Harvard University.
*/

#include "Arduino.h"
#include "SapphireMotor.h"

#define MAX_SPEED 255

SapphireMotor::SapphireMotor(int digitalPinNumber, int pwmPinNumber)
{
	// configure the Arduino pins
	pinMode(digitalPinNumber, OUTPUT);
	pinMode(pwmPinNumber, OUTPUT);
	
	// set the variables representing the pin numbers;
	this->_digitalPinNumber = digitalPinNumber;
	this->_pwmPinNumber = pwmPinNumber;
	
	// set the initial state for the motor
	stop();
}

void SapphireMotor::moveForward(int speed)
{
	// check that speed is between 1 and maximum speed
	if(speed > 0 && speed <= MAX_SPEED)
	{
		// set the speed in the PWM pin
		analogWrite(this->_pwmPinNumber, speed);
		
		// if the motor is not in the same direction already, set the pin
		if(this->_currentState != TOFORWARD)
		{
			digitalWrite(this->_digitalPinNumber, HIGH);
		}
		
		// set the new state
		this->_currentState = TOFORWARD;
	}
}

void SapphireMotor::moveBackward(int speed)
{
	// check that speed is between 1 and maximum speed
	if(speed > 0 && speed <= MAX_SPEED)
	{
		// set the speed in the PWM pin
		analogWrite(this->_pwmPinNumber, speed);
		
		// if the motor is not in the same direction already, set the pin
		if(this->_currentState != TOBACKWARD)
		{
			digitalWrite(this->_digitalPinNumber, LOW);
		}
		
		// set the new state
		this->_currentState = TOBACKWARD;
	}
}

void SapphireMotor::stop()
{
	if(this->_currentState != STOPPED)
	{
		// set to low the pins to stop the motion
		digitalWrite(this->_pwmPinNumber, LOW);
		digitalWrite(this->_digitalPinNumber, LOW);
		
		// set the new state
		this->_currentState = STOPPED;
	}
}