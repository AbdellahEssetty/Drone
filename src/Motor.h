#include <Arduino.h>
#include <Servo.h>

class Motor
{
public:
  Motor(int pin):
  pin(pin)
  {
    ESC.attach(pin);
    Serial.println("Motor attached to pin" + pin);
  }

  void write(int iSpeed)
  {
    speed = iSpeed > 180 ? 180 : iSpeed;
  }

  void increaseSpeed(int dV = 3)
  {
    speed += dV;
    speed = speed > 180 ? 180 : speed;
  }

  void run()
  {
    Serial.println(speed);
    ESC.write(speed);
  }

  int getSpeed()const
  {
    return speed;
  }

private:
  Servo ESC;
  const int pin;
  int speed = 0;
};

