#include "Coin.h"
#include "Button.h"
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define COIN_PIN_1 A0
#define COIN_PIN_2 A1
#define COIN_PIN_3 A2
#define COIN_PIN_4 A3
#define COIN_PIN_5 A4
#define BUTTON1_PIN 7
#define BUTTON2_PIN 8

Coin coin1(COIN_PIN_1);
Coin coin2(COIN_PIN_2);
Coin coin3(COIN_PIN_3);
Coin coin4(COIN_PIN_4);
Coin coin5(COIN_PIN_5);

Button button1(BUTTON1_PIN);
Button button2(BUTTON2_PIN);

int besKurus = 0;
int onKurus = 0;
int yirmiBesKurus = 0;
int elliKurus = 0;
int birLira = 0;
int n = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop() {
  int besKurusVal = coin1.readValue();
  int onKurusVal = coin2.readValue();
  int yirmiBesKurusVal = coin3.readValue();
  int elliKurusVal = coin4.readValue();
  int birLiraVal = coin5.readValue();

  if (button1.isPressed()){
    n++;
  }

  if (button2.isPressed()){
    n--;
  }
  
  n = (n == 6) ? 0 : n;
  n = (n == -1) ? 5 : n;

  besKurus = (besKurusVal < 100) ? besKurus + 1 : besKurus;
  onKurus = (onKurusVal < 100) ? onKurus + 1 : onKurus;
  yirmiBesKurus = (yirmiBesKurusVal < 100) ? yirmiBesKurus + 1 : yirmiBesKurus;
  elliKurus = (elliKurusVal < 100) ? elliKurus + 1 : elliKurus;
  birLira = (birLiraVal < 100) ? birLira + 1 : birLira;
  
  switch (n) {
    case 1:
      updateDisplay(besKurus, 5);
      break;
    case 2:
      updateDisplay(onKurus, 10);
      break;
    case 3:
      updateDisplay(yirmiBesKurus, 25);
      break;
    case 4:
      updateDisplay(elliKurus, 50);
      break;
    case 5:
      updateDisplay(birLira, 1);
      break;
    default:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("  Para Sayici");
      lcd.setCursor(0,1);
      lcd.print("  Toplam: ");
      int toplam = besKurus + onKurus + yirmiBesKurus + elliKurus + birLira;
      lcd.print(toplam);
      break;
  }
  
  delay(100);
}

void updateDisplay(int val, int type) {
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print(type);
   if (type == 1) {
    lcd.print(" lira: ");
   } else {
    lcd.print(" kurus: ");
   }
   lcd.print(val);
}
