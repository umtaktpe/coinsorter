#include "Motor.h"

Motor::Motor(byte pin) {
  this->pin = pin;
  init();
}

void Motor::init() {
  pinMode(pin, OUTPUT);
}

void Motor::startMotor() {
  digitalWrite(pin, HIGH);
}

void Motor::stopMotor() {
  digitalWrite(pin, LOW);
}
