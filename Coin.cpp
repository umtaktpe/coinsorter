#include "Coin.h"

Coin::Coin(byte pin) {
  this->pin = pin;
  init();
}

void Coin::init() {
  pinMode(pin, INPUT);
}

int Coin::readValue() {
  return analogRead(pin);
}
