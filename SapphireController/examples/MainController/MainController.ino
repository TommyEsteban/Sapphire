/*
  Main sketch to control the Sapphire vehicle
  Created by Tommy E. Garcia, November 26, 2015.
  Released as a part of the final project for CS50 course from Harvard University.
*/

#include <Wire.h>
#include <LSM303.h>
#include <NewPing.h>
#include <SoftwareSerial.h>
#include <SapphireMotor.h>
#include <SapphireServo.h>
#include <SapphireMotion.h>
#include <SapphireVision.h>
#include <SapphireController.h>

// table of the used pins
#define dirPinLeftMotor 8
#define speedPinLeftMotor 10
#define dirPinRightMotor 7
#define speedPinRightMotor 9
#define servoPin A3
#define echoPin 5
#define triggerPin 4
#define MAX_RANGE 400
#define LEADPIN 13

// this is the main controller object
SapphireController controller(LEADPIN);

void setup() {

  // initialize the motion system
  controller.initializeMotion(dirPinLeftMotor, speedPinLeftMotor, dirPinRightMotor, speedPinRightMotor);

  // initialize the vision system
  controller.initializeVision(servoPin, SERVO180, echoPin, triggerPin, MAX_RANGE);
}

void loop() {

  // run the autonomouse mode
  controller.runAutonomousMode();
}
