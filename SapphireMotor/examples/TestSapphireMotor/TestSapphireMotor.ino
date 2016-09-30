/*
  Sketch to test the Shapphire motor library
  Created by Tommy E. Garcia, November 26, 2015.
  Released as a part of the final project for CS50 course from Harvard University.
*/

#include <SapphireMotor.h>

// pin to control the motor direction
#define DIR_PIN 7

// pin to control the motor speed
#define SPEED_PIN 9

// the first argument of the constructor is a conventional digital pin and the second argument must be a digital PWM pin
SapphireMotor motor(DIR_PIN, SPEED_PIN);

void setup() {

}

void loop() {

  // move the motor forward speeding up from 100 to 150 (max speed)
  for(int s = 100; s < 150; s++)
  {
    motor.moveForward(s);
    delay(100);
  }

  motor.stop();
  delay(2000);

  // move the motor backward decelerating from 150 to 100 (min speed)  
  for(int s = 150; s > 100; s--)
  {
    motor.moveBackward(s);
    delay(100);
  }

  // stop the motor
  motor.stop();
  delay(2000);

  // go backward
  motor.moveBackward(100);
  delay(2000);

  // stop the motor
  motor.stop();
  delay(1000);

  // go forward
  motor.moveForward(100);
  delay(2000);
}
