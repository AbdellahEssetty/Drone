#include <Arduino.h>
#include "Motor.h"
#include "Directions.h"
class Drone
{
public:
  Drone(int p1, int p2, int p3, int p4):
  fL(Motor(p1)),
  fR(Motor(p2)),
  rR(Motor(p3)),
  rL(Motor(p4))
  {
    Serial.println("Init drone");
  }

//Read the data from the app and change the direction of the drone.
  void applyDirection()
  {
    switch (order)
    {
    case Directions::up:
      goUp();
      break;
    case Directions::down:
      goDown();
      break;
    case Directions::front:
      goFront();
      break;
    case Directions::right:
      goRight();
      break;
    case Directions::back:
      goBack();
      break;
    case Directions::left:
      goLeft();
      break;
    case Directions::stabilize:
      stabilize();
      break;
    default:
      break;
    }
  }

//Get the data from the bluetooth app.
  char getBTData()
  {
    short tolerance = 100;
    while (--tolerance > 0)
    {
      if(Serial.available())
      {
        order = Serial.read(); 
        break;
      }
      delay(1);
    }
    return order;
  }

//The drone goes in vertical direction up.
//Basically stabilize the drone then increase the speed of each motor.
  void goUp()
  {
    // Stabilize in case of changing direction.
    //stabilize();
    increaseSpeed(2, 2, 2, 2);
  }

// The drone goes down vertically.
  void goDown()
  {
    increaseSpeed(-2, -2, -2, -2);
  }  

  void goFront()
  {
    increaseSpeed(-2, -2, 2, 2);
  }

  void goBack()
  {
    increaseSpeed(2, 2, -2, -2);
  }

  void goRight()
  {
    increaseSpeed(2, -2, -2, 2);
  }

  void goLeft()
  {
    increaseSpeed(-2, 2, 2, -2);
  }

//Increase/decrease the speed of the motors(respectivelly) front-left, front-right, 
//rear-right and rear-left. 
  void increaseSpeed(int fLdV, int fRdV, int rRdV, int rLdV)
  {
    fL.increaseSpeed(fLdV);
    fR.increaseSpeed(fRdV);
    rR.increaseSpeed(rRdV);
    rL.increaseSpeed(rLdV);
  }

//Stabilize the drone if its not. Will be used as tranzition between going to directions
//and going up/down.
  void stabilize()
  {
    int mean = (fL.getSpeed() + fR.getSpeed() + rR.getSpeed() + rL.getSpeed()) / 4;
    Motor motors[4] = {fL, fR, rR, rL};
    //Getting the data gentily to the mean.
    for (size_t i = 0; i < 4; i++)
    {
      while(motors[i].getSpeed() != mean)
      {
        //The speed should increase if it is less than the mean, decrease otherwise.
        byte sign = motors[i].getSpeed() < mean ? 1 : -1;
        motors[i].increaseSpeed(sign * 1);
      }
    }
    
  }

// Run the four motors at their speed.
  void run()
  {
    fL.run();
    fR.run();
    rR.run();
    rL.run();
  }
private:

//The 4 four motors front-left, front-right, rear-right and rear-left.
  Motor fL;
  Motor fR;
  Motor rR;
  Motor rL;

  char order;
};
