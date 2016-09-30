/*
  SapphireMotion.h - Library to control the motion of Sapphire vehicle based on two DC motors.
  Created by Tommy E. Garcia, November 26, 2015.
  Released as a part of the final project for CS50 course from Harvard University.
*/

#ifndef SapphireMotion_h
#define SapphireMotion_h

#include "Arduino.h"
#include "Wire.h"
#include "LSM303.h"
#include "SapphireMotor.h"

class SapphireMotion
{
	public:
		// default constructor
		SapphireMotion();
		
		// The constructor contains 4 arguments which are the pins to associate to the left motor and right motor,
		// every motor uses one digital pin to control the direction and one PWM pin to control the speed
		SapphireMotion(int digitalPinLeftMotor, int pwmPinLeftMotor, int digitalPinRightMotor, int pwmPinRightMotor);
		
		// initialize the motion system
		void initialize(int digitalPinLeftMotor, int pwmPinLeftMotor, int digitalPinRightMotor, int pwmPinRightMotor);
		
		// put all the available motors to forward at the same speed
		void goForward(int speed);
		
		// put all the available motors to forward at different speed
		void goForward(int speedLeft, int speedRight);
		
		// put all the available motors to backward at the same speed
		void goBackward(int speed);
		
		// put all the available motors to backward at different speed
		void goBackward(int speedLeft, int speedRight);
	
		// stop all the motors
		void stop();
		
		// turn to the left with a given speed by moving forward the right motor and moving backward the left motor
		void turnLeft(int speed);
		
		// turn to the left by moving forward the right motor and moving backward the left motor
		// the magnetometer and accelerometer are used to rotate approximately until the given angle
		void turnLeft(int speed, int angle);
		
		// turn to the right with a given speed by moving forward the left motor and moving backward the right motor
		void turnRight(int speed);
		
		// turn to the right by moving forward the left motor and moving backward the right motor
		// the magnetometer and accelerometer are used to rotate approximately until the given angle
		void turnRight(int speed, int angle);
	
	private:
		// two pointer to the ShappireMotor class, one for the left motor and one for the right motor
		SapphireMotor *_left, *_right;
		
		// the compass controller (accelerometer and magnetometer)
		LSM303 _compass;
};

#endif