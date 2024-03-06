// get Serial No
String getSerialNo(uint32_t id, bool secondTime=false ){
  // check if sent
  if (CAN.sendMsgBuf(id, 0, 8, get_serialNo_command) != 0){
    return "ERROR/1018: no CAN device found%";
  }
  delay(5);
  
  
  // get response
  int r_id = 0 ;
  unsigned char r_buf[8];
  getResponse(&r_id, r_buf);
  
  
  // check ID
  if ((r_id + 0x80) != id){
    return "ERROR/1018: incorrect id%";
  }
  
  
  // validate
  String controller_id = "0x";
  if (checkArrayIdentical(r_buf, serialNo_reply_OK_command)){
    for (int i = 7 ; i >= 4 ; i--) {
      if (String(r_buf[i],HEX).length() == 2)
        controller_id += String(r_buf[i],HEX);
      else
        controller_id = controller_id + "0" + String(r_buf[i],HEX);
    }
  }
  else {
    return "ERROR/1018: response void error ";
  }
  

  return controller_id;
}


// send command 
String sendCommand(uint32_t id,  uint8_t *buf){
  // check if sent
  if (CAN.sendMsgBuf(id, 0, 8, buf) != 0){
    return "ERROR/60" + String(buf[1], HEX) + ": no CAN device found%";
  }
  delay(5);


  // get response
  int r_id = 0 ;
  unsigned char r_buf[8];
  getResponse(&r_id, r_buf);

  // check ID
  if ((r_id + 0x80) != id){
    return "ERROR/60" + String(buf[1], HEX) + ": incorrect id%";
  }


  // validate
  if (buf == shutdown_command){
    return (checkArrayIdentical(r_buf, controlWord_reply_OK_command)) ? "OK" : "ERROR/60" + String(buf[1], HEX) + ": response void error%";
  }
  else if (buf == switchon_command){
    return (checkArrayIdentical(r_buf, controlWord_reply_OK_command)) ? "OK" : "ERROR/60" + String(buf[1], HEX) + ": response void error%";
  }
  else if (buf == enop_command){
    return (checkArrayIdentical(r_buf, controlWord_reply_OK_command)) ? "OK" : "ERROR/60" + String(buf[1], HEX) + ": response void error%";
  }
  else if (buf == MA_command){
    return (checkArrayIdentical(r_buf, controlWord_reply_OK_command)) ? "OK" : "ERROR/60" + String(buf[1], HEX) + ": response void error%";
  }
  else if (buf == setPosition){
    return (checkArrayIdentical(r_buf, setPosition_reply_OK_command)) ? "OK" : "ERROR/60" + String(buf[1], HEX) + ": response void error%";
  }
  else if (buf == setVelocity){
    return (checkArrayIdentical(r_buf, setVelocity_reply_OK_command)) ? "OK" : "ERROR/60" + String(buf[1], HEX) + ": response void error%";
  }
  else if (buf == position_mode_command){
    return (checkArrayIdentical(r_buf, modes_reply_OK_command)) ? "OK" : "ERROR/60" + String(buf[1], HEX) + ": response void error%";
  }
  else if (buf == velocity_mode_command){
    return (checkArrayIdentical(r_buf, modes_reply_OK_command)) ? "OK" : "ERROR/60" + String(buf[1], HEX) + ": response void error%";
  }
  else 
    return "ERROR/NA: line 86";

}
