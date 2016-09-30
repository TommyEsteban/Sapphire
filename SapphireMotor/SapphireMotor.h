/*
  SapphireMotor.h - Library to control one DC motor based on H-Bridge.
  Created by Tommy E. Garcia, November 26, 2015.
  Released as a part of the final project for CS50 course from Harvard University.
*/

#ifndef SapphireMotor_h
#define SapphireMotor_h

#include "Arduino.h"

// the different states of the motor
enum State { STOPPED, TOFORWARD, TOBACKWARD };

class SapphireMotor
{
  public:
    
	// Initialize the pins used to control the motor
	// two pins must be provided for initialization, one for control the state and one PWM based for speed
	SapphireMotor(int digitalPinNumber, int pwmPinNumber);

	// move the motor forward in a given speed from 1 to 255
    void moveForward(int speed);
	
	// move the motor backward in a given speed from 1 to 255
    void moveBackward(int speed);
	
	// stop the motor
	void stop();
	
	private:
	
	// variable to control the state of the motor
	State _currentState;
	
	// pin number used to control the direction the motor direction
	int _digitalPinNumber;
	
	// pin number used to control the motor speed
	int _pwmPinNumber;
};

#endif