/*
  SapphireServo.h - Library to control one servo motor.
  based on the code provided by Pololu: https://www.pololu.com/docs/0J57/8.a
  Created by Tommy E. Garcia, November 26, 2015.
  Released as a part of the final project for CS50 course from Harvard University.
*/

#ifndef SapphireServo_h
#define SapphireServo_h

#include "Arduino.h"

enum ServoType { SERVO360, SERVO180 };

class SapphireServo
{
  public:
    
	// variable to set the state of the initialization of the servo
	bool isInitialized = false;
	
	// default constructor
	SapphireServo();
	
	// initialize the servo by associating one pin number and the type of the servo
	// it can be 360 degrees servo or 180 degree servo
	void initialize(int pin, ServoType type);
	
	// set the values used to map the minimum and maximum times in microseconds 
	// with degrees for 180 degrees servos and 360 degrees servos, if the servoType is 180 degrees
	// the minTime corresponds to the servo in the position of 0 degrees 
	// and the maxTime corresponds to the servo in the position of 180 degrees
	void setMappingValues(int minTime, int maxTime);
	
	// set the position of the servo motor based in pulse time (microseconds)
	void setPositionMicro(uint16_t highTimeMicroseconds);
	
	// set the position of the servo with a given amount in degrees, 
	// use the setCalibrationValues function before to map correctly the position
	void setPosition(int degrees);
	
  private:
	
	// pin number to provide the signal to the servo motor
	int _pin;
	
	// the maximum time in microseconds to send the pulse
	int _maxTime = 2500;
	
	// the maximum time in microseconds to send the pulse
	int _minTime = 600;
	
	// the _the minimum angle that the servo can move, usually it is zero
	int _minAngle = 0;
	
	// the maximum angle that the servo can move, by default is 180
	int _maxAngle = 180;
	
	// the servo type, 360 degrees servo or 180 degrees servo
	ServoType _type;
};

#endif