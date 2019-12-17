#include <Arduino.h>

class Motor {
  private:
    byte pin;
  
  public:
    Motor(byte pin);
    void init();
    void startMotor();
    void stopMotor();
};
