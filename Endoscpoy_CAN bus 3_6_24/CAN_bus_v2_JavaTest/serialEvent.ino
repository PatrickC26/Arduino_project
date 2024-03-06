void serialEvent(){
  char inC = Serial.read();
  delay(5);
//  Serial.println(inC);
  if (inC == 'a')
    readVoid(CAN_1, "a");
    
  else if (inC == 'b')
    readVoid(CAN_2, "b");
  
  else if (inC == 'c')
    readVoid(CAN_3, "c");

  else
    Serial.println("ERROR: tag mismatch: " + inC);
}


void readVoid(int id, String tag){
  char inC = Serial.read();
  delay(5);
//  Serial.println(inC);
  
  
  if (inC == 'A'){ // check connection
    String serialNo = getSerialNo(id);
    if (serialNo.indexOf("ERROR") >= 0)
      Serial.println(tag + "P0%");
    else {
      Serial.println(tag + "P1%");
      Serial.println(tag + "N" + serialNo + "%");
    }
  }

  else if (inC == 'B'){// Enable
    String shutdown_reply = sendCommand(id, shutdown_command);
    String turnOn_reply = sendCommand(id, switchon_command);
    String enop_reply = sendCommand(id, enop_command);
    
    if (shutdown_reply != "OK") 
      Serial.println(tag + shutdown_reply);
    else if (turnOn_reply != "OK") 
      Serial.println(tag + turnOn_reply);
    else if (enop_reply != "OK")
      Serial.println(tag + enop_reply);
    else
      Serial.println(tag + "KB%");
  }
  
  else if (inC == 'C'){ // Disable
    String shutdown_reply = sendCommand(id, shutdown_command);
    if (shutdown_reply == "OK")
      Serial.println(tag + "KC%");
    else 
      Serial.println(tag + "KC%");
  }

  else if (inC == 'D'){ //setPosition
    String inS = Serial.readString();

    // check HEX header and ender
    if ((inS.indexOf("0x") < 0) || (inS.indexOf("%") < 0)){
      Serial.println( tag + "ERROR/D: token not found");
      return;
    }
    inS = inS.substring(inS.indexOf("0x")+2, inS.indexOf("%"));
//    Serial.println(inS);

    // Check length
    if (inS.length() > 8) {
      Serial.println( tag + "ERROR/D: length longer than 8");
      return;
    }
    
    // convert to HEX
    long sum = 0 ;
    int val[4] = {0,0,0,0};
    for (int i = inS.length() -1 , j = 1; i >= 0  ; i --, j++){
      int inB = hexTable(inS[i]);
      if (inB == -1) {
        Serial.println( tag + "ERROR/D: not HEX");
        break;
      }

      // store value to val
      if (j%2 == 0)
        val [j/2-1] = (inB * 16 + hexTable(inS[i+1]));
      else if (i == 0)  {
        val [j/2] = inB ;
      }
    }

    // set position
    setPosition[7] = val[3];
    setPosition[6] = val[2];
    setPosition[5] = val[1];
    setPosition[4] = val[0];


    // send commands
    String setPos_reply = sendCommand(id, setPosition);
    String enop_reply = sendCommand(id, enop_command);
    String ma_reply = sendCommand(id, MA_command);

    if (setPos_reply != "OK") 
      Serial.println(tag + setPos_reply);
    else if (enop_reply != "OK")
      Serial.println(tag + enop_reply);
    else if (ma_reply != "OK") 
      Serial.println(tag + ma_reply);
    else
      Serial.println(tag + "KD%");
  }

  else if (inC == 'M'){
    int inI = Serial.parseInt();
    int inI2 = inI%256;
    inI -= inI2;
    inI /= 256;

    setVelocity[4] = inI2;
    setVelocity[5] = inI;
    setVelocity[6] = 0;
    setVelocity[7] = 0;

    String setV = sendCommand(id, setVelocity);
    if (setV == "OK")
      Serial.println(tag + "KM%");
    else 
      Serial.println(tag + setV);
  }

  else if (inC == 'Q'){
    if (tag == "a")
      responseRequested_1 = (Serial.read() == '1');
    else if (tag == "b")
      responseRequested_2 = (Serial.read() == '1');
    else if (tag == "c")
      responseRequested_3 = (Serial.read() == '1');
  }
  else
    Serial.println("ERROR: void mismatch: " + inC);
}
