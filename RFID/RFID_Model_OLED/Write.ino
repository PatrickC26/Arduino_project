void write(){
  Serial.println("waiting for card to write");
  
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle. And if present, select one.
  while (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial());
  
  Serial.println("Writing to card");
  
  // Set new UID
  if (mfrc522.MIFARE_SetUid(UID, (byte)4, true) ) {
    Serial.println("Success");
    screen.clearDisplay();
    screen.setFont(&FreeSans12pt7b);
    screen.setCursor(45, 40); // (x,y)
    screen.println("OK");
    screen.display();
    delay(2000);
  }
  else {
    Serial.println("Clone fail");
    screen.clearDisplay();
    screen.setFont(&FreeSans12pt7b);
    screen.setCursor(30, 40); // (x,y)
    screen.println("Failed");
    screen.display();
    delay(2000);
  }
  
  
  // Halt PICC and re-select it so DumpToSerial doesn't get confused
  mfrc522.PICC_HaltA();
  screen.clearDisplay();
  screen.setFont(&FreeSans9pt7b);
  screen.setCursor(13, 40); // (x,y)
  screen.print(UID[0],HEX);
  screen.print(' ');
  screen.print(UID[1],HEX);
  screen.print(' ');
  screen.print(UID[2],HEX);
  screen.print(' ');
  screen.print(UID[3],HEX);
  screen.display();
}
