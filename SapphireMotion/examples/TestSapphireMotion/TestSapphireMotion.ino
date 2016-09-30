/*
  Sketch to test the Shapphire motion library
  Created by Tommy E. Garcia, November 26, 2015.
  Released as a part of the final project for CS50 course from Harvard University.
*/

#include <Wire.h>
#include <LSM303.h>
#include <SapphireMotor.h>
#include <SapphireMotion.h>

//define the pin numbers to be used in this test
#define LEFT_PIN_DIR 8
#define LEFT_PIN_SPEED 10
#define RIGHT_PIN_DIR 7
#define RIGHT_PIN_SPEED 9

// the motion object
SapphireMotion motion;

void setup() {
  
  // first argument is the pin number used to control the left motor direction
  // second argument is the pin number used to control the left motor speed 
  // third argument is the pin number used to control the right motor direction
  // last argument is the pin number used to control the right motor speed
  motion.initialize(LEFT_PIN_DIR, LEFT_PIN_SPEED, RIGHT_PIN_DIR, RIGHT_PIN_SPEED);
}

void loop() {
  
  // go to forward speeding up from 1 to 255 (max speed)
  for(int s = 1; s < 255; s++)
  {
    motion.goForward(s);
    delay(100);
  }

  // stop motion two seconds
  motion.stop();
  delay(2000);

  // go to backward decelerating from 255 to 1 (min speed)  
  for(int s = 255; s > 1; s--)
  {
    motion.goBackward(s);
    delay(100);
  }

  // stop motion
  motion.stop();
  delay(2000);

  // turn left
  motion.turnLeft(150);
  delay(2000);

  // stop motion
  motion.stop();
  delay(1000);

  // turn right
  motion.turnRight(150);
  delay(2000);

  motion.stop();
  delay(2000);
}
