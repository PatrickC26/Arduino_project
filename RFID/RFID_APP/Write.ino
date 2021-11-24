void RFID_rewrite_UID(String UID){
  String UID_origional = "";
  char UID_C[23];
  UID.toCharArray(UID_C,23);
  
  if (UID_C[0] == 'U' && UID_C[1] == 'I' && UID_C[2] == 'D'){
    byte newUid[4] = {(C2I(UID_C[5])*16+C2I(UID_C[6])),(C2I(UID_C[10])*16+C2I(UID_C[11])),(C2I(UID_C[15])*16+C2I(UID_C[16])),(C2I(UID_C[20])*16+C2I(UID_C[21]))};
    
    // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle. And if present, select one.
    while (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial());

    // Dump UID
    for (byte i = 0; i < mfrc522.uid.size; i++) {  // 逐一顯示UID碼
      UID_origional = UID_origional+"0x"+String(mfrc522.uid.uidByte[i], HEX)+"-";       // 以16進位顯示UID值
    } 

    // Set new UID
    if ( mfrc522.MIFARE_SetUid(newUid, (byte)4, true) ) {
      Serial.println("S");
      BTH.println("S");
    }
    else {
      Serial.println("E");
      BTH.println("E");
    }
    
    
    // Halt PICC and re-select it so DumpToSerial doesn't get confused
    mfrc522.PICC_HaltA();
    
    // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle. And if present, select one.
    
  }
}
