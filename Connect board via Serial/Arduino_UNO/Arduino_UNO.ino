#include <SoftwareSerial.h>
SoftwareSerial Serial4(10,11);//(RX,TX)

void setup() {
  Serial.begin(9600);
  Serial4.begin(9600);
  Serial4.write("");
  Serial.println("begin");
  Serial.println("Please type your interger message below");
}

void serialEvent() {
  while (Serial.available()){
    char incomingByte = Serial.read();
    Serial.print(incomingByte);
    Serial4.write(incomingByte);
  } 
}
void loop() {
  while(Serial4.available()) {
    while('@' != Serial4.read()) { 
    }
    int howManyValueShouldGetinSerial1=2;
    for(int i=1; i<=howManyValueShouldGetinSerial1; i++) {
      int n = Serial4.parseInt();
      switch(i){
        case 1: //isConnected?
          bool isConnect = bool(n);
          digitalWrite(13,isConnect);
          Serial.println(isConnect);
          break;
        case 2: //isBreakApply
          bool isBreakApp=bool(n);
          Serial.println(isBreakApp);
      }
    }
  }
  
}
