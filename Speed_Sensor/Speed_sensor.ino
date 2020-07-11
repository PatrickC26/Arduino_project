#include <LiquidCrystal_I2C.h>
bool botton,lbotton;
int ms,lms=ms=0;
double ts,sv,hv=0,lhv;
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // 設定 LCD I2C 位址

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

 void loop(){
    //----------------------------if dectect-------------------------------
    botton= digitalRead(53);
    if (botton==0&&lbotton!=0){
      ms=millis();
      ts=ms-lms;
      sv=66.04/2/*tire radious*/*360/16/ts;
      hv=sv/3.6;
      lms=ms;
    }
    else if (ms-lms>500){
      ts=ms-lms;
      lms=ms;
      sv=hv=0;
      lcd.setCursor(0,1);
      lcd.print("Speed");
      lcd.print(0.00);
      lcd.print("km/hr ");
    }
    
    if (lhv!=hv){//-------------show value------------------------------
      Serial.print(ts);
      Serial.print(" ms");
      Serial.print("  \t");
     /* Serial.print(sv);
      Serial.print(" m/s");
      Serial.print("\t");*/
      Serial.print(hv);
      Serial.println(" km/hr ");
      lhv=hv;
      lcd.setCursor(0,1);
      lcd.print("Speed");
      lcd.print(hv);
      lcd.print("km/hr ");
    }
    lbotton = botton;
  }
