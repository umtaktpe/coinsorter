#include <Arduino.h>

class Button {
  private:
    byte pin;
    bool buttonState = LOW;
  public:
    Button(byte pin);
    void init();
    bool update();
    bool debounceButton(bool state);
    bool isPressed();
};
