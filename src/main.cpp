#include <Arduino.h>
#include <Servo.h>
#include "Drone.h"



char input = 0;
Drone drone = Drone(6, 7, 8, 9);

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  drone.getBTData();
  drone.applyDirection();

  delay(100);


}
