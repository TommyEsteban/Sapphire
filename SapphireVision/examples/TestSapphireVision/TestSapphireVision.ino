/*
  Sketch to test the Shapphire motion library
  Created by Tommy E. Garcia, November 26, 2015.
  Released as a part of the final project for CS50 course from Harvard University.
*/

#include <NewPing.h>
#include <SapphireServo.h>
#include <SapphireVision.h>

#define SERVO_PIN A3
#define ECHO_PIN 5
#define TRIGGER_PIN 4
#define MAX_RANGE 400

SapphireVision vision;

void setup() {
  
  // firt argument is the pin used for servo motor, 
  // second argument is the servo type 180 degrees or 360 degrees
  // next arguments are the pins used for the ultrasonic sensor, echo and trigger pins
  // last argument is the maximum range of distance of the ultrasonic sensor
  vision.initialize(SERVO_PIN, SERVO180, ECHO_PIN, TRIGGER_PIN, MAX_RANGE);

  // initialize the serial ports
  Serial.begin(9600);

  // set the vision to the front and wait 100 milliseconds
  vision.setToFront(100);
}

void loop() {

  // get instant reading of the distance to the nearest object in centimeters
  unsigned long distance = vision.getDistance();
  Serial.print("Current distance: "); 
  Serial.print(distance);
  Serial.println(" cm");

  delay(1000);
  
  // the getAverageDistance function takes multiple readings of distances, 
  // discard out of range pings and return median in centimeters, 
  // the parameter is the number of readings
  unsigned int averageDistance = vision.getAverageDistance(5);
  Serial.print("Average distance: "); 
  Serial.print(averageDistance);
  Serial.println(" cm");
  
  // move the vision to 0 degrees position and wait 500 milliseconds
  vision.move(0, 500);

  // move the vision to 90 degrees position and wait 500 milliseconds
  vision.move(90, 500);

  // move the vision to 180 degrees position and wait 500 milliseconds
  vision.move(180, 500);

  // look around and get distances every degree.
  Serial.println("scanning... ");
  vision.scan();

  // restore to the original position and wait 100 milliseconds
  vision.setToFront(100);

  // print distances from the last scan
  for(int i = 0; i <= 180; i++)
  {
    Serial.print("In "); 
    Serial.print(i);
    Serial.print(" degrees ");
    Serial.print("object to "); 
    Serial.print(vision.distances[i]);
    Serial.println(" cm ");
  }

  delay(30000);
}
