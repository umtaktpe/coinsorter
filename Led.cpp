#include "Led.h"

Led::Led(byte pin) {
  this->pin = pin;
  init();
}

void Led::init() {
  pinMode(pin, OUTPUT);
  off();
}

void Led::on() {
  digitalWrite(pin, HIGH);
}

void Led::off() {
  digitalWrite(pin, LOW);
}

void Led::blinkLed() {
  int val = 0;
  while (val < 5) {
    digitalWrite(pin, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(300);                       // wait for a second
    digitalWrite(pin, LOW);    // turn the LED off by making the voltage LOW
    delay(300);
    val++;
  } 
}
