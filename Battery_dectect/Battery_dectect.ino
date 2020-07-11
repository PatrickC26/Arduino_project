#include <LiquidCrystal_I2C.h>
  LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // 設定 LCD I2C 位址

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
lcd.begin(16,2);
}

void loop(){
    Serial.print(analogRead(A1));
    double bat = map (analogRead(A1),0,1023,0,1500);
    Serial.print("  Battery:");
    Serial.print((bat/100.00));
    Serial.println(" V");
    int percent =map(bat,1150,1300,0,100);
    if (bat>=1000){
      lcd.setCursor(13,0);
      lcd.print(percent);
    }
    else {
      lcd.setCursor(14,0);
      lcd.print(percent);
    }
    lcd.setCursor(15,0);
    lcd.print("%   ");
  }
