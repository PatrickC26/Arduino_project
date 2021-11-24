String RFID_read(){
  String a ="UID";
  int t = 0;
  while (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    if (t<300)  t++;
    else break;
  }
  if (t<300){
    byte *id = mfrc522.uid.uidByte;   // 取得卡片的UID
    for (byte i = 0; i < mfrc522.uid.size; i++) {  // 逐一顯示UID碼
      a = a+"0x"+String(mfrc522.uid.uidByte[i], HEX)+"-";       // 以16進位顯示UID值
    }
    a = a + "=";
    mfrc522.PICC_HaltA();  // 讓卡片進入停止模式
  }
  else a = "E";
  BTH.println(a);
  return a;
}
