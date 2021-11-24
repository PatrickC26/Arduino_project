void read(){
  Serial.println("Waiting for card to read");
  
  //Waiting to read
  while (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) ;
    byte *id = mfrc522.uid.uidByte;   // 取得卡片的UID

    screen.clearDisplay();
    screen.setFont(&FreeSans9pt7b);
    screen.setCursor(13, 40);
    //Print uid
    for (byte i = 0; i < mfrc522.uid.size; i++) {  // 逐一顯示UID碼
      UID[i]=mfrc522.uid.uidByte[i];
      Serial.print(UID[i],HEX);
      Serial.print('-');
      screen.print(UID[i],HEX);
      screen.print(' ');
      
      //Print Error if error occur
      if (UID[i]==0){
        Serial.println("ERROR in reading");
        screen.setFont(&FreeSans12pt7b);
        while (1){
          screen.setCursor(20, 40); // (x,y)
          screen.println("ERROR");
          screen.display();
          delay(500);
          screen.clearDisplay();
          screen.setCursor(20, 40); // (x,y)
          screen.println("      ");
          screen.display();
          delay(500);
        }
      }
    }
    screen.display();
    Serial.println("");
    mfrc522.PICC_HaltA();  // 讓卡片進入停止模式
    Serial.println("go to write()");
    write();
}
