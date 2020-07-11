#include<Servo.h>
Servo SPX1;
Servo SPX2;
//------------------------------setup----------------------------------------------
  void setup() {
    Serial.begin(9600);
    SPX1.attach(A7);
    SPX2.attach(A8);
    SPX1.write(93);
    SPX2.write(93);
    Serial.println("BREAK STOP");
  }

  void SPX(int v){
    SPX1.write(v);
    SPX2.write(v);
  }

void loop() {
  // put your main code here, to run repeatedly:
   while(Serial.available()){
     int valueFromComputer=Serial.parseInt();
     if (valueFromComputer!=0){
        SPX (valueFromComputer);
        Serial.println(valueFromComputer);
       }
   }
}
