#include <SoftwareSerial.h>

const int rxpin = 2; // 接收 pin
const int txpin = 3; // 發送 pin

SoftwareSerial Serial2(rxpin, txpin); // 建立虛擬序列埠

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600); // 初始化藍芽序列埠
  Serial2.println("at");
  delay(1000);
  Serial2.println("at+cpin?");
  delay(1000);
  Serial2.println("at+creg?");
  delay(1000);
  Serial2.println("at+cgatt?");
  delay(1000);
  Serial2.println("at+cipshut");
  delay(1000);
  Serial2.println("at+cipstatus");
  delay(1000);
  Serial2.println("at+cipmux=0");
  delay(1000);
//  Serial2.println("at");
//  Serial2.println("at");
}
void loop(){
  
}
void serialEvent() {
  while (Serial2.available()){
    char c = Serial2.read();
    Serial.print(c);
  }
  while (Serial.available()){
    char c = Serial.read();
    Serial2.print(c);
  }
//  delay(1000);
//Serial.println(digitalRead(4));
}
