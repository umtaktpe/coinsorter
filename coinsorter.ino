#include "Coin.h"
#include "Button.h"
#include "Led.h"
#include <EEPROM.h>
#include <LiquidCrystal.h>
#include <String.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define COIN_PIN_1 A0
#define COIN_PIN_2 A1
#define COIN_PIN_3 A2
#define COIN_PIN_4 A3
#define COIN_PIN_5 A4
#define BUTTON1_PIN 7
#define BUTTON2_PIN 8
#define BUTTON3_PIN 9
#define GREEN_LED 6
#define YELLOW_LED 10
#define RED_LED 13

Coin coin1(COIN_PIN_1);
Coin coin2(COIN_PIN_2);
Coin coin3(COIN_PIN_3);
Coin coin4(COIN_PIN_4);
Coin coin5(COIN_PIN_5);

Button button1(BUTTON1_PIN);
Button button2(BUTTON2_PIN);
Button button3(BUTTON3_PIN);

Led greenLed(GREEN_LED);
Led yellowLed(YELLOW_LED);
Led redLed(RED_LED);

int besKurus = 0;
int onKurus = 0;
int yirmiBesKurus = 0;
int elliKurus = 0;
int birLira = 0;
int n = 0;
int addr = 0;
String menuItem[7] = {
  "5 kurus sifirla",
  "10kurus sifirla",
  "25kurus sifirla",
  "50kurus sifirla",
  "1 lira sifirla",
  "Hepsini sifirla",
  "Cikis"
};

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  greenLed.on();
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

  if (button3.isPressed()) {
    menu();
  }
  
  n = (n == 6) ? 0 : n;
  n = (n == -1) ? 5 : n;

  besKurus = (besKurusVal < 20) ? besKurus + 1 : EEPROM.read(0);
  onKurus = (onKurusVal < 100) ? onKurus + 1 : EEPROM.read(1);
  yirmiBesKurus = (yirmiBesKurusVal < 100) ? yirmiBesKurus + 1 : EEPROM.read(2);
  elliKurus = (elliKurusVal < 20) ? elliKurus + 1 : EEPROM.read(3);
  birLira = (birLiraVal < 20) ? birLira + 1 : EEPROM.read(4);

  int myVals[5] = {besKurus, onKurus, yirmiBesKurus, elliKurus, birLira};
  for (addr; addr < 5; addr++) {
    EEPROM.write(addr, myVals[addr]);
  }

  addr = 0;

  switch (n) {
    case 1:
      updateDisplay(EEPROM.read(0), 5);
      break;
    case 2:
      updateDisplay(EEPROM.read(1), 10);
      break;
    case 3:
      updateDisplay(EEPROM.read(2), 25);
      break;
    case 4:
      updateDisplay(EEPROM.read(3), 50);
      break;
    case 5:
      updateDisplay(EEPROM.read(4), 1);
      break;
    default:
      int toplam = besKurus + onKurus + yirmiBesKurus + elliKurus + birLira;
      displayMenu("   Para Sayici", "   Toplam: " + String(toplam));
      break;
  }

  fullnessStates();
  
  delay(100);
}

void menu() { 
  int m = 0;
  int y = 0;
  while (m != -2) {
    if (button1.isPressed()) {
      y++;
    }

    if (button2.isPressed()) {
      y--;
    }

    if (y == 0) {
      displayMenu(" --Secenekler--", menuItem[0]);
    }
    
    if (y == 1) {
      displayMenu(String(">") + menuItem[0], menuItem[1]);
      if (button3.isPressed()) {
        EEPROM.write(0, 0);
        greenLed.on();
        redLed.off();
        yellowLed.blinkLed();
        displayMenu("     5kurus", "   sifirlandi");
        delay(2000);
        yellowLed.off();
      }
    }

    if (y == 2) {
      displayMenu(String(">") + menuItem[1], menuItem[2]);
      if (button3.isPressed()) {
        EEPROM.write(1, 0);
        greenLed.on();
        redLed.off();
        yellowLed.blinkLed();
        displayMenu("     10kurus", "   sifirlandi");
        delay(2000);
        yellowLed.off();
      }
    }

    if (y == 3) {
      displayMenu(String(">") + menuItem[2], menuItem[3]);
      if (button3.isPressed()) {
        EEPROM.write(2, 0);
        greenLed.on();
        redLed.off();
        yellowLed.blinkLed();
        displayMenu("     25kurus", "   sifirlandi");
        delay(2000);
        yellowLed.off();
      }
    }

    if (y == 4) {
      displayMenu(String(">") + menuItem[3], menuItem[4]);
      if (button3.isPressed()) {
        EEPROM.write(3, 0);
        greenLed.on();
        redLed.off();
        yellowLed.blinkLed();
        displayMenu("     50kurus", "   sifirlandi");
        delay(2000);
        yellowLed.off();
      }
    }

    if (y == 5) {
      displayMenu(String(">") + menuItem[4], menuItem[5]);
      if (button3.isPressed()) {
        EEPROM.write(4, 0);
        greenLed.on();
        redLed.off();
        yellowLed.blinkLed();
        displayMenu("     1 lira", "   sifirlandi");
        delay(2000);
        yellowLed.off();
      }
    }

    if (y == 6) {
      displayMenu(String(">") + menuItem[5], menuItem[6]);
      if (button3.isPressed()) {
        for (int x = 0; x < 5; x++) {
          EEPROM.write(x, 0);
        }
        greenLed.on();
        redLed.off();
        displayMenu("  Tum paralar", "   sifirlandi");
        yellowLed.blinkLed();
        delay(2000);
        yellowLed.off();
      }
    }

    if (y == 7) {
      displayMenu(menuItem[5], String(">") + menuItem[6]);
      if (button3.isPressed()) {
        m = -2;
      }
    }

     y = (y == 8) ? 0 : y;
     y = (y == -1) ? 0 : y;
     delay(100);
    }
}

void fullnessStates() {
  int q = 0;
  int states[5] = {0, 0, 0, 0, 0};
  int coins[5] = {5, 10, 25, 50, 1};
  int fullStates[5] = {};
  int arraySum = 0;

  if (EEPROM.read(0) == 20) {
    states[0] = 1;
  }

  if (EEPROM.read(1) == 20) {
    states[1] = 1;
  }

  if (EEPROM.read(2) == 20) {
    states[2] = 1;
  }

  if (EEPROM.read(3) == 20) {
    states[3] = 1;
  }

  if (EEPROM.read(4) == 20) {
    states[4] = 1;
  }

  for (int i = 0; i < 5; i++) {
    if (states[i] == 1) {
      fullStates[i] = coins[i];
    }
  }

  for (int i = 0; i < 5; i++) {
    arraySum += fullStates[i];
  }
  
  if (arraySum != 0) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Dolu hazneler");
    for (int i = 0; i < 5; i++) {
        if(fullStates[i] != 0) {
          lcd.setCursor(0, i);
          lcd.print(fullStates[i]);
          greenLed.off();
          redLed.on();
          while (q != -1) {
            if (button3.isPressed()) {
              n = 0;
              q = -1;
           }
          }
         }
    }
  } else {
    return 1;
  }
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

void displayMenu(String text1, String text2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(text1);
  lcd.setCursor(0, 1);
  lcd.print(text2);
}
