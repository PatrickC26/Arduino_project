//
//// get position
//long getPosition(uint32_t id){
//  // check if sent
//  if (CAN.sendMsgBuf(id, 0, 8, get_position_command) != 0){
//    Serial.println("ERROR with sending");
//    return 0xF0000000;
//  }
//  delay(5);
//
//
//  // get response
//  int r_id = 0 ;
//  unsigned char r_buf[8];
//  getResponse(&r_id, r_buf);
//
//
//  // check ID
//  if ((r_id + 0x80) != id){
//    Serial.println("ERROR with wrong id");
//    return 0xF0000000;
//  }
//
//  
//  // to long
//  long pos = 0;
//  if (checkArrayIdentical(r_buf, getPosition_reply_OK_command)){
//    for (int i = 7 ; i >= 4 ; i--) {
//      pos += r_buf[i]*_FF_pow[i-4];
//    }
//  }
//  else return 0xF0000000;
//  if (pos > 0xF0000000){
//    pos = pos - 0xFFFFFFFF-1;
//  }
//
//  
//  return pos;
//}
//
//
//// get speed
//long getVelocity(uint32_t id){
//  // check if sent
//  if (CAN.sendMsgBuf(id, 0, 8, get_velocity_command) != 0){
//    Serial.println("ERROR with sending");
//    return 0xF0000000;
//  }
//  delay(5);
//
//
//  // get response
//  int r_id = 0 ;
//  unsigned char r_buf[8];
//  getResponse(&r_id, r_buf);
//
//
//  // check ID
//  if ((r_id + 0x80) != id){
//    Serial.println("ERROR with wrong id");
//    return 0xF0000000;
//  }
//
//  
//  // to long
//  long speed_v = 0;
//  if (checkArrayIdentical(r_buf, getVelocity_reply_OK_command)){
//    for (int i = 7 ; i >= 4 ; i--) {
//      speed_v += r_buf[i]*_FF_pow[i-4];
//    }
//  }
//  else return 0xF0000000;
//  if (speed_v > 0xF0000000){
//    speed_v = speed_v - 0xFFFFFFFF-1;
//  }
//
//  
//  return speed_v;
//}



// get position
long getPosition(uint32_t id){
  return getInfo(id, get_position_command);
}


// get speed
long getVelocity(uint32_t id){
  return getInfo(id, get_velocity_command);
}


// get amper
long getAmper(uint32_t id){
  return getInfo(id, get_amper_command);
}


// get temperature
long getTemperature(uint32_t id){
  return getInfo(id, get_temp_command);
}


long getInfo(uint32_t id, uint8_t *buf){
  String tag = "";

  if (id == CAN_1) tag = "a";
  else if (id == CAN_2) tag = "b";
  else if (id == CAN_3) tag = "c";
  
  
    // check if sent
  if (CAN.sendMsgBuf(id, 0, 8, buf) != 0){
    Serial.println(tag + "ERROR/60" + String(buf[1]) + ": no CAN device found%");
    return 0xF0000000;
  }
  delay(5);


  // get response
  int r_id = 0 ;
  unsigned char r_buf[8];
  getResponse(&r_id, r_buf);


  // check ID
  if ((r_id + 0x80) != id){
    Serial.println(tag + "ERROR/60" + String(buf[1]) + ": incorrect id%");
    return 0xF0000000;
  }

  
  // to long
  long data = 0;
  bool result = false;

  if (buf == get_velocity_command){
    result = checkArrayIdentical(r_buf, getVelocity_reply_OK_command) ;
  }
  else if (buf == get_position_command){
    result = checkArrayIdentical(r_buf, getPosition_reply_OK_command) ;
  }
  else if (buf == get_amper_command){
    result = checkArrayIdentical(r_buf, getAmper_reply_OK_command) ;
  }
  else if (buf == get_temp_command){
    result = checkArrayIdentical(r_buf, getTemp_reply_OK_command) ;
  }

  
  if (result){
    for (int i = 7 ; i >= 4 ; i--) {
      data += r_buf[i]*_FF_pow[i-4];
    }
  }
  else return 0xF0000000;

  if (data > 0xF0000000){
    data = data - 0xFFFFFFFF-1;
  }

  
  return data;
}
