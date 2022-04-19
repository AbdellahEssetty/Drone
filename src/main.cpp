#include <Arduino.h>
#include <Servo.h>


enum Directions
{
  down = '0',
  up = '1',
  front = '2',
  right = '3',
  back = '4', 
  left = '5'
};
class Motor
{
public:
  Motor(int pin):
  pin(pin)
  {
    ESC.attach(pin);
  }
  void write(int iSpeed)
  {
    speed = iSpeed > 180 ? 180 : iSpeed;
  }
  void increaseSpeed()
  {
    speed += 5;
    speed = speed > 180 ? 180 : speed;
  }
  void run()
  {
    Serial.println(speed);
    ESC.write(speed);
  }
private:
  Servo ESC;
  const int pin;
  int speed = 0;
};


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

  void getBTData(char data)
  {
    switch (data)
    {
    case Directions::up:
      goUp();
      break;
    case Directions::down:
      break;
    case Directions::front:
      break;
    case Directions::right:
      break;
    case Directions::back:
      break;
    case Directions::left:
      break;

    default:
      break;
    }
  }

  void goUp()
  {
    fL.increaseSpeed();
    fR.increaseSpeed();
    rR.increaseSpeed();
    rL.increaseSpeed();

    run();
    
  }

  void run()
  {
    fL.run();
    fR.run();
    rR.run();
    rL.run();
  }
private:
  Motor fL;
  Motor fR;
  Motor rL;
  Motor rR;
};

char input = 0;
Drone drone = Drone(6, 7, 8, 9);

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  if(Serial.available() > 0)
  {
    input = Serial.read();
    if(input == Directions::up)
    { 
      drone.goUp();
    }
    Serial.println(input);
  }

  delay(100);


}
