#include <SoftwareSerial.h>

const int rxpin = 2; // 接收 pin
const int txpin = 3; // 發送 pin
<<<<<<< HEAD
SoftwareSerial Serial2(rxpin, txpin); // 建立虛擬序列埠
=======

SoftwareSerial Serial2(rxpin, txpin); // 建立虛擬序列埠

>>>>>>> f7ad32efd050a94771eabaaec7236192cd4bb2c9
void setup() {
  Serial.begin(9600);
  Serial2.begin(9600); // 初始化藍芽序列埠
}
void loop() {
//  Serial2.print("AT");
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
