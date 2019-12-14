#include <Arduino.h>

class Coin {
  private:
    byte pin;
  public:
    Coin(byte pin);
    void init();
    int readValue();
};
