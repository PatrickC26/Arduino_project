void write(){
  Serial.println("waiting for card");
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle. And if present, select one.
  while (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial());
  digitalWrite(greenLED,0);
  analogWrite(blueLED,10);
  delay(300);
  digitalWrite(blueLED,0);
  
  Serial.println("Writing to card");

  // Set new UID
  if (mfrc522.MIFARE_SetUid(UID, (byte)4, true) ) {
    Serial.println("Success");
    analogWrite(greenLED,10);
    delay(1000);
  }
  else {
    Serial.println("fail");
    while(1) analogWrite(redLED,10);
  }
  
  
  // Halt PICC and re-select it so DumpToSerial doesn't get confused
  mfrc522.PICC_HaltA();
  for(int i = 0 ; i <5 ;i++){
    digitalWrite(greenLED,0);
    analogWrite(blueLED,10);
    delay(400);
    digitalWrite(blueLED,0);
    analogWrite(greenLED,10);
    delay(400);
  }
}
