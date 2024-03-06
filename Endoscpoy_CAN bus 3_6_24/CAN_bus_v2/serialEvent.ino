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
  else if (inC == 'U'){
    Serial.println("UTEST1.1.0.20231018%");
  }
  else if (inC == '%');
  

  else
    Serial.println("ERROR/tag mismatch: tag is " + inC);
}


void readVoid(int id, String tag){
  char inC = Serial.read();
  delay(5);
//  Serial.println(inC);
  
  
  if (inC == 'A'){ // check connection
    String serialNo = getSerialNo(id);
    if (serialNo.indexOf("-") >= 0){
      Serial.println(tag + "P0%");
      CAN.begin(CAN_125KBPS);
    }
    else {
      Serial.println(tag + "P1%");
      Serial.println(tag + "N" + serialNo + "%");
      
      
      if (tag == "a") {
        if (!responseRequested_1){
          responseRequested_1 = true;
          connectionerror_1 = 0;
        }
      }
      else if (tag == "b") {
        if (!responseRequested_2){
          responseRequested_2 = true;
          connectionerror_2 = 0;
        }
      }
      else if (tag == "c") {
        if (!responseRequested_3){ 
          responseRequested_3 = true;
          connectionerror_3 = 0;
        }
      }
        
    }
  }

  else if (inC == 'B'){// Enable    
    if (!disable(id)) 
      Serial.println(tag + "ERROR/B: shutdown error%");
    else if (!switchon(id))
      Serial.println(tag + "ERROR/B: switchOn error%");
    else if (!enop(id))
      Serial.println(tag + "ERROR/B: enop error%");
    else
      Serial.println(tag + "KB%");
  }
  
  else if (inC == 'C'){ // Disable
    if (!disable(id)) 
      Serial.println(tag + "ERROR/C: shutdown error%");
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
    setPosition_command[7] = val[3];
    setPosition_command[6] = val[2];
    setPosition_command[5] = val[1];
    setPosition_command[4] = val[0];


    // send commands
    if (!setPosition(id)) 
      Serial.println( tag + "ERROR/D: setPosition error");
    else if (!enop(id))
      Serial.println( tag + "ERROR/D: ENOP error");
    else if (!MA(id)) 
      Serial.println( tag + "ERROR/D: MA error");
    else
      Serial.println(tag + "KD%");
  }

  else if (inC == 'M'){
    int inI = Serial.parseInt();
    int inI2 = inI%256;
    inI -= inI2;
    inI /= 256;

    setVelocity_command[4] = inI2;
    setVelocity_command[5] = inI;
    setVelocity_command[6] = 0;
    setVelocity_command[7] = 0;

    if (setVelocity(id))
      Serial.println(tag + "KM%");
    else 
      Serial.println(tag + "ERROR/M: setVelocity error");
  }

  else if (inC == 'Q'){
    if (tag == "a")
      responseRequested_1 = (Serial.read() == '1');
    else if (tag == "b")
      responseRequested_2 = (Serial.read() == '1');
    else if (tag == "c")
      responseRequested_3 = (Serial.read() == '1');

    if (responseRequested_1) connectionerror_1 = 0;
    if (responseRequested_2) connectionerror_2 = 0;
    if (responseRequested_3) connectionerror_3 = 0;
  }
  else
    Serial.println("ERROR/void mismatch: input is -> " + inC);
}
