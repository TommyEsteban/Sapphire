/*
  Sketch to test the servo motor library
  Created by Tommy E. Garcia, November 26, 2015.
  Released as a part of the final project for CS50 course from Harvard University.
*/

#include <SapphireServo.h>

// the pin used for the servo
#define SERVO_PIN A3

// the servo object
SapphireServo servo;

void setup() {

  // initialize the servo motor specifying the pin number and the servo type
  // in this sample it is a 180 degrees servo motor.
  servo.initialize(SERVO_PIN, SERVO180);
}

void loop() {
  
  // go from 0 to 180 degrees
  for(int i = 0; i <= 180; i++)
  {
    servo.setPosition(i);
    delay(20);
  }

  delay(1000);
}
