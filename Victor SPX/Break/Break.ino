  #include <Wire.h>  // Arduino IDE 內建
  #include <LiquidCrystal_I2C.h>
  #include<Servo.h>
  
  LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // 設定 LCD I2C 位址
  Servo SPX1;
  Servo SPX2;
  int b=1;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println("Start");
SPX1.attach(A7);
SPX2.attach(A8);
SPX2.write(93);
SPX(93);
}
void SPX(int deg){
  SPX1.write(deg);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available()){
    b = Serial.parseInt();
    Serial.println(b);
  }
    int no = 5;
  if (b==1){
      SPX(93);
      for (int i=0 ; i<=no ; i++){
        SPX(95+i);
        delay(30);
      }
      for (int i=0 ; i<=no ; i++){
        SPX(95-i);
        delay(30);
      }
      SPX(93);
      for (int i=0 ; i<=no ; i++){
        SPX(90-i);
        delay(30);
      }
      for (int i=0 ; i<=no ; i++){
        SPX(90+i);
        delay(30);
      }
      SPX(93);
      Serial.println("Break Apply");
  }
  if (b==2){
    SPX(4);
  }
  else {
    SPX(93);
  }
}
