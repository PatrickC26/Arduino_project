#include <Wire.h>  // Arduino IDE 內建
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // 設定 LCD I2C 位址

  void setup() {
    Serial.begin(9600);    
    lcd.begin(16, 2);      // 初始化 LCD，一行 16 的字元，共 2 行，預設開啟背光
    Serial.println("START");
    for(int i = 0; i < 3; i++) {
        lcd.backlight(); // 開啟背光
        delay(250);
        lcd.noBacklight(); // 關閉背光
        delay(250);
      }
      lcd.backlight();
      lcd.setCursor(0,0); // set cursor at first line first alphabet
      lcd.print("Initializing");
      delay(100);
      lcd.print(".");
      delay(100);
      lcd.print(".");
      delay(100);
      lcd.print(".");
      delay(1000);
      lcd.clear();
      delay(500);
      lcd.print("SET");
      delay(1000);
      lcd.clear();

      
  }
void loop() {
      lcd.setCursor(0,1);
      lcd.print("Speed");
      lcd.print("20");
      lcd.print("km/hr");

      lcd.setCursor(0,0);
      lcd.print((100-93)*100/52);
      lcd.print("%");
      lcd.setCursor(10,0);
      lcd.print("9");
      lcd.print("%");

  }
