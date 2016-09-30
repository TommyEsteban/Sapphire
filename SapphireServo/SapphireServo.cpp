/*
  SapphireServo.cpp - Library to control one servo motor.
  based on the code provided by Pololu: https://www.pololu.com/docs/0J57/8.a
  Created by Tommy E. Garcia, November 26, 2015.
  Released as a part of the final project for CS50 course from Harvard University.
*/

#include "SapphireServo.h"

// This line specifies what pin we will use for sending the signal to the servo.
int SERVO_PIN = 11;

// This is the time since the last rising edge in units of 0.5us.
uint16_t volatile servoTime = 0;
 
// This is the pulse width we want in units of 0.5us.
uint16_t volatile servoHighTime = 3000;
 
// This is true if the servo pin is currently high.
boolean volatile servoHigh = false;

SapphireServo::SapphireServo()
{
}

void SapphireServo::initialize(int pin, ServoType type)
{
	// set the limits depending of the servo type
	if(type == SERVO360)
	{
		this->_maxTime = 4400;
		this->_minTime = 600;
		this->_minAngle = 0;
		this->_maxAngle = 360;
	}
	else
	{
		this->_maxTime = 2500;
		this->_minTime = 600;
		this->_minAngle = 0;
		this->_maxAngle = 180;
	}
	
	// configure the pins
	SERVO_PIN = pin;
	digitalWrite(SERVO_PIN, LOW);
	pinMode(SERVO_PIN, OUTPUT);
   
	// Turn on CTC mode.  Timer 2 will count up to OCR2A, then
	// reset to 0 and cause an interrupt.
	TCCR2A = (1 << WGM21);
	// Set a 1:8 prescaler.  This gives us 0.5us resolution.
	TCCR2B = (1 << CS21);

	// Put the timer in a good default state.
	TCNT2 = 0;
	OCR2A = 255;

	TIMSK2 |= (1 << OCIE2A);  // Enable timer compare interrupt.
	sei();   // Enable interrupts.
	
	this->isInitialized = true;
}

void SapphireServo::setMappingValues(int minTime, int maxTime)
{
	this->_minTime = minTime;
	this->_maxTime = maxTime;
}

// This ISR runs after Timer 2 reaches OCR2A and resets.
// In this ISR, we set OCR2A in order to schedule when the next
// interrupt will happen.
// Generally we will set OCR2A to 255 so that we have an
// interrupt every 128 us, but the first two interrupt intervals
// after the rising edge will be smaller so we can achieve
// the desired pulse width.
ISR(TIMER2_COMPA_vect)
{
	// The time that passed since the last interrupt is OCR2A + 1
	// because the timer value will equal OCR2A before going to 0.
	servoTime += OCR2A + 1;

	static uint16_t highTimeCopy = 3000;
	static uint8_t interruptCount = 0;
   
	if(servoHigh)
	{
		if(++interruptCount == 2)
		{
			OCR2A = 255;
		}

		// The servo pin is currently high.
		// Check to see if is time for a falling edge.
		// Note: We could == instead of >=.
		if(servoTime >= highTimeCopy)
		{
			// The pin has been high enough, so do a falling edge.
			digitalWrite(SERVO_PIN, LOW);
			servoHigh = false;
			interruptCount = 0;
		}
	} 
	// The servo pin is currently low.
	else
	{
		if(servoTime >= 40000)
		{
			// We've hit the end of the period (20 ms),
			// so do a rising edge.
			highTimeCopy = servoHighTime;
			digitalWrite(SERVO_PIN, HIGH);
			servoHigh = true;
			servoTime = 0;
			interruptCount = 0;
			OCR2A = ((highTimeCopy % 256) + 256)/2 - 1;
		}
	}
}

void SapphireServo::setPositionMicro(uint16_t highTimeMicroseconds)
{
	// disable timer compare interrupt
	TIMSK2 &= ~(1 << OCIE2A); 
	servoHighTime = highTimeMicroseconds * 2;
	
	// enable timer compare interrupt
	TIMSK2 |= (1 << OCIE2A); 
}

void SapphireServo::setPosition(int degrees)
{
	// check that given angle is between the limits of the servo motor
	if(degrees >= this->_minAngle && degrees <= this->_maxAngle)
	{
		// map angles to times and get the position by the given microseconds
		uint16_t microseconds = map(degrees, this->_minAngle, this->_maxAngle, this->_minTime, this->_maxTime);
		setPositionMicro(microseconds);
	}
}