#include <Wire.h>  // Arduino IDE 內建
#include <LiquidCrystal.h>

LiquidCrystal lcd(1, 2, 4, 5, 6, 7);  // 設定 LCD I2C 位址

  void setup() {
    Serial.begin(9600);
    Serial.print("START");
  // ----------------------------LCD--------------------------
    lcd.begin(16, 2);      // 初始化 LCD，一行 16 的字元，共 2 行，預設開啟背光
  //Blink three times
    for(int i = 0; i < 2; i++) {
      //lcd.blink(); // 開啟背光
      
    }
lcd.clear();
  }

void loop() {

  
  // 輸出初始化文字
    lcd.setCursor(0, 0); // 設定游標位置在第一行行首
    lcd.print("Initializing");
          lcd.setCursor(0,11);
          int vol=3;
      lcd.print(vol*3);
lcd.setCursor(0,0);
           
           lcd.print((100-93)/52);

      
    delay(1000);
    //lcd.clear();


}
