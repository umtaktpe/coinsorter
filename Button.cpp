#include "Button.h"

Button::Button(byte pin) {
  this->pin = pin;
  init();
}

void Button::init() {
  pinMode(pin, INPUT);
}

bool Button::update() {
  if(debounceButton(buttonState) == HIGH && buttonState == LOW){
    buttonState = HIGH;
  } else if(debounceButton(buttonState) == LOW && buttonState == HIGH){
    buttonState = LOW;
  }

  return buttonState;
}

bool Button::debounceButton(bool state) {
  bool stateNow = digitalRead(pin);
  if(state!=stateNow) {
    delay(10);
    stateNow = digitalRead(pin);
  }
  
  return stateNow;
}

bool Button::isPressed() {
  return update();
}
