void getResponse(int *id,  uint8_t *buf){
  unsigned char len = 0;
  for (int i = 0 ; i < 5 ; i++){
    if(CAN_MSGAVAIL == CAN.checkReceive()) {
      CAN.readMsgBuf(&len, buf);   // read data,  len: data length, buf: data buf
      *id = CAN.getCanId();
      return true;
    }
  }
  return false;
}


void checkResponse_reply(){
  unsigned char len = 0;
  unsigned char buf[8];
  
  for (int i = 0 ; i < 5 ; i++){
    if(CAN_MSGAVAIL == CAN.checkReceive()) {  // check if data coming
//      Serial.println("INSIDE");
      CAN.readMsgBuf(&len, buf);   // read data,  len: data length, buf: data buf
      int id = CAN.getCanId();

      Serial.print(id, HEX);
      
      for(int i = 0; i<len; i++) {  // print the data
          Serial.print("\t");
          Serial.print(int(buf[i]), HEX);
      }
      Serial.println("\n");
      break;
    }
  }
}
