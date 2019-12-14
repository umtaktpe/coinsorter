#include "Coin.h"
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define COIN_PIN_1 A0
#define COIN_PIN_2 A1
#define COIN_PIN_3 A2
#define COIN_PIN_4 A3
#define COIN_PIN_5 A4
#define BUTTON_PIN 7

Coin coin1(COIN_PIN_1);
Coin coin2(COIN_PIN_2);
Coin coin3(COIN_PIN_3);
Coin coin4(COIN_PIN_4);
Coin coin5(COIN_PIN_5);

int besKurus = 0;
int onKurus = 0;
int yirmiBesKurus = 0;
int elliKurus = 0;
int birLira = 0;
int n = 0;
bool buttonState = LOW; 

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
  
  if(debounceButton(buttonState) == HIGH && buttonState == LOW){
    n++;
    buttonState = HIGH;
  } else if(debounceButton(buttonState) == LOW && buttonState == HIGH){
    buttonState = LOW;
  }
  
  n = (n == 6) ? 0 : n;

  besKurus = (besKurusVal < 100) ? besKurus + 1 : besKurus;
  onKurus = (onKurusVal < 100) ? onKurus + 1 : onKurus;
  yirmiBesKurus = (yirmiBesKurusVal < 100) ? yirmiBesKurus + 1: yirmiBesKurus;
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

boolean debounceButton(boolean state) {
  boolean stateNow = digitalRead(BUTTON_PIN);
  if(state!=stateNow)
  {
    delay(10);
    stateNow = digitalRead(BUTTON_PIN);
  }
  return stateNow; 
}
