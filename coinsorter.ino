#include "Coin.h"
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define COIN_PIN_1 A0
#define COIN_PIN_2 A1

Coin coin1(COIN_PIN_1);
Coin coin2(COIN_PIN_2);

int besKurus = 0;
int onKurus = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  besKurus += coin1.readValue();
  onKurus += coin2.readValue();

  lcd.print(besKurus);
  Serial.print("Sensor1: ");
  Serial.println(besKurus);
  Serial.print("Sensor2: ");
  Serial.println(onKurus);
  delay(100);
}
