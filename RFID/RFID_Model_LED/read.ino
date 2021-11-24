void read(){
  Serial.println("Waiting for card to read");
  while (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    digitalWrite(blueLED,0);
    delay(300);
    analogWrite(blueLED,10);
    delay(300);
  }
  digitalWrite(blueLED,0);
  analogWrite(greenLED,10);
    byte *id = mfrc522.uid.uidByte;   // 取得卡片的UID
    for (byte i = 0; i < mfrc522.uid.size; i++) {  // 逐一顯示UID碼
      UID[i]=mfrc522.uid.uidByte[i];
      Serial.print(UID[i],HEX);
      Serial.print('-');
      if (UID[i]==0){
        digitalWrite(blueLED,0);
        digitalWrite(greenLED,0);
        while (1)analogWrite(redLED,10);
      }
    }
    Serial.println("");
    mfrc522.PICC_HaltA();  // 讓卡片進入停止模式
    delay(300);
    digitalWrite(greenLED,0);
    analogWrite(greenLED,10);
    delay(300);
    digitalWrite(greenLED,0);
    analogWrite(greenLED,10);
    delay(1000);
//    Serial.println("go to write()");
    write();
}
