long getFinalPosition(unsigned char a[]){
  long data = 0;

  for (int i = 7 ; i >= 4 ; i--) {
    data += a[i] * _FF_pow[i-4];
  }
  
  return data;
}

long getPosition(uint32_t id, bool doSerial = false){
  return getInfo(id, get_position_command, doSerial);
}

long getVelocity(uint32_t id, bool doSerial = false){
  return getInfo(id, get_velocity_command, doSerial);
}

long getAmper(uint32_t id, bool doSerial = false){
  return getInfo(id, get_amper_command, doSerial);
}

long getTemperature(uint32_t id, bool doSerial = false){
  return getInfo(id, get_temp_command, doSerial);
}

String getSerialNo(uint32_t id, bool doSerial = false){
  return String(getInfo(id, get_serialNo_command, doSerial));
}

bool disable(uint32_t id, bool doSerial = false){
  return bool(getInfo(id, shutdown_command, doSerial) == 1);
}

bool switchon(uint32_t id, bool doSerial = false){
  return bool(getInfo(id, switchon_command, doSerial) == 1);
}

bool enop(uint32_t id, bool doSerial = false){
  return bool(getInfo(id, enop_command, doSerial) == 1);
}

bool MA(uint32_t id, bool doSerial = false){
  return bool(getInfo(id, MA_command, doSerial) == 1);
}

bool setPosition(uint32_t id, bool doSerial = false){
  return bool(getInfo(id, changePosition_Directommand, doSerial) == 1);
}

bool setVelocity(uint32_t id, bool doSerial = false){
  return bool(getInfo(id, setVelocity_Directommand, doSerial) == 1);
}

bool setPositionsystemMode(uint32_t id, bool doSerial = false){
  return bool(getInfo(id, position_systemMode_command, doSerial) == 1);
}

bool setVelocitysystemMode(uint32_t id, bool doSerial = false){
  return bool(getInfo(id, velocity_systemMode_command, doSerial) == 1);
}



// get information 
long getInfo(uint32_t id, uint8_t *buf, bool doSerial){
  String tag = "";

  // check tag
  if (id == CAN_id[0]) tag = "a";
  else if (id == CAN_id[1]) tag = "b";
  else if (id == CAN_id[2]) tag = "c";
  
  
  // check if sent
  if (CAN.sendMsgBuf(id, 0, 8, buf) != 0){
    if(doSerial || doSerial_global)
      Serial.println(tag + "ERROR/" + String(buf[1], HEX) + ": no CAN device found%");
    
    return 0xF0000000;
  }
  delay(5);


  // get response
  int r_id = 0 ;
  unsigned char r_buf[8];
  getResponse(&r_id, r_buf);


  // check ID
  
  if ((r_id + 0x80) != id){
    if (r_id == id){
      if(doSerial || doSerial_global)
        Serial.println(tag + "ERROR/" + String(buf[1], HEX) + ": no response%");
      return 0xF0000000;
    }
    else {
      String dataS = "";
      for (int i = 0 ; i < 8 ; i++){
        dataS = dataS + String(r_buf[i], HEX) + "," ;
      }
      if(doSerial || doSerial_global)
        Serial.println(tag + "ERROR/" + String(buf[1], HEX) + ": error response id: " + String(id, HEX) + "\t" + dataS + "%");
      return 0xF0000000;
    }
  }

  
  // check response validation
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
  else if (buf == get_serialNo_command){
    result = checkArrayIdentical(r_buf, serialNo_reply_OK_command) ;
  }
  else if (buf == shutdown_command){
    return (checkArrayIdentical(r_buf, controlWord_reply_OK_command)) ? 1 : 0;
  }
  else if (buf == switchon_command){
    return (checkArrayIdentical(r_buf, controlWord_reply_OK_command)) ? 1 : 0;
  }
  else if (buf == enop_command){
    return (checkArrayIdentical(r_buf, controlWord_reply_OK_command)) ? 1 : 0;
  }
  else if (buf == MA_command){
    return (checkArrayIdentical(r_buf, controlWord_reply_OK_command)) ? 1 : 0;
  }
  else if (buf == changePosition_Directommand){
    return (checkArrayIdentical(r_buf, setPosition_reply_OK_command)) ? 1 : 0;
  }
  else if (buf == setVelocity_Directommand){
    return (checkArrayIdentical(r_buf, setVelocity_reply_OK_command)) ? 1 : 0;
  }
  else if (buf == position_systemMode_command){
    return (checkArrayIdentical(r_buf, systemModes_reply_OK_command)) ? 1 : 0;
  }
  else if (buf == velocity_systemMode_command){
    return (checkArrayIdentical(r_buf, systemModes_reply_OK_command)) ? 1 : 0;
  }
  else{
    String dataS = "";
    for (int i = 0 ; i < 8 ; i++){
      dataS = dataS + "," + (String)(r_buf[i]);
    }
    
//    if(doSerial || doSerial_global)
    Serial.println(tag + "ERROR/" + String(buf[1], HEX) + ": incorrect response with output" + dataS + "%");
    
    return 0xF0000000;
  }
  


  // get result
  long data = 0;
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
