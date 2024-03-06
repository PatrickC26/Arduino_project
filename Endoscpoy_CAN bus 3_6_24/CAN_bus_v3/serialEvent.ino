void serialEvent(){
  char inC = Serial.read();
  delay(5);
  if (inC == 'a')
    readVoid(0);
    
  else if (inC == 'b')
    readVoid(1);
  
  else if (inC == 'c')
    readVoid(2);
  else if (inC == 'U'){
    Serial.println("UTEST1.1.0.20231018%");
  }
  else if (inC == '%');
  else if (inC == 'I'){
    systemMode = modeName_user;
    changePosition_Directommand[4] = 0;
    changePosition_Directommand[5] = 0;
    changePosition_Directommand[6] = 0;
    changePosition_Directommand[7] = 0;
    enable_C(0);
    changePosition_Direct(0);
    enable_C(1);
    changePosition_Direct(1);
    enable_C(2);
    changePosition_Direct(2);

    setVelocity_Direct(0,velocity_normalSpeed);
    setVelocity_Direct(1,velocity_normalSpeed);
    setVelocity_Direct(2,velocity_normalSpeed);
  }
  else if (inC == 'F'){
    int moveDistance = Serial.parseInt();

    if (CAN_id[2] == 0x601){
      changePosition_Relative_Direct_WaitUntil(2, moveDistance);
      Serial.println("KF%");
    }
    else{
      Serial.println("\n\n ----- Forward " + String(moveDistance) + " steps------ \n\n");
      moveForward(moveDistance);
    }
    
  }
  else if (inC == 'B'){// Enable    
    enable_C(2);
    systemMode = modeName_user;
  }
  else if (inC == 'C'){ // Disable
    disable_Direct(2);
    systemMode = modeName_disable;
  }
  else if (inC == 'S'){
    int inI = Serial.parseInt();

    Serial.println("KS%");
    if (doSerial_global)
      Serial.println("\n\n ----- Moving Speed " + String(inI) + " steps------ \n\n");

    setVelocity_Direct(2,inI);
  }
  else if (inC == 'R'){
    Serial.println("\n\n ----- Release ------ \n\n");
    changePosition_Direct_WaitUnitl(0, setPosition_front_open);
    changePosition_Direct_WaitUnitl(1, setPosition_rear_open);
  }
  else if (inC == 'G'){
    Serial.println("\n\n ----- Grasp ------ \n\n");
    changePosition_Direct_WaitUnitl(0, setPosition_front_close);
    changePosition_Direct_WaitUnitl(1, setPosition_rear_close);
  }
  else if (inC == 'T'){
    Serial.println("\n ------ Testing ------ \n");
    changePosition_Relative_Direct_WaitUntil(2,1000);
//    changePosition_Direct_WaitUnitl(2,1000);
    Serial.println("\n ------- Done ---------\n");
  }
  else if (inC == 'W'){
    Serial.println("\n ------ auto cal motor 2 ------ \n");
    autoCalibration(1,1);
    Serial.println("\n ------ auto cal motor 1 ------ \n");
    autoCalibration(0,1);
    Serial.println("\n ------ auto cal motor 3 ------ \n");
    autoCalibration(2,1);
    long2array(motor_a_pos[0], setPosition_front_open);
    long2array(motor_b_pos[0], setPosition_front_close);
    long2array(motor_a_pos[1]-0x500, setPosition_rear_open);
    long2array(motor_b_pos[1], setPosition_rear_close);    
  }
  else if (inC == 'Z'){
    Serial.println("\n ------ auto cal motor 3 ------ \n");
    autoCalibration(2,1);
  }
  else if (inC == 'Y'){
    Serial.println("\n ------ auto cal motor 2 ------ \n");
    autoCalibration(1,1);
  }
  else if (inC == 'X'){
    Serial.println("\n ------ auto cal motor 1 ------ \n");
    autoCalibration(0,1);
  }

  else
    Serial.println("ERROR/tag mismatch: tag is " + inC);
}


void readVoid(int no){
  int id = CAN_id[no];
  String tag = tagA[no];
  
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
        if (!responseRequested[0]){
          responseRequested[0] = true;
          connectionStatus[0] = 1;
          connectionerror[0] = 0;
        }
      }
      else if (tag == "b") {
        if (!responseRequested[1]){
          responseRequested[1] = true;
          connectionStatus[1] = 1;
          connectionerror[1] = 0;
        }
      }
      else if (tag == "c") {
        if (!responseRequested[2]){ 
          responseRequested[2] = true;
          connectionStatus[2] = 1;
          connectionerror[2] = 0;
        }
      }
    }
  }

  else if (inC == 'B'){// Enable    
    enable_C(no);
  }
  
  else if (inC == 'C'){ // Disable
    disable_Direct(no);
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
    changePosition_Directommand[7] = val[3];
    changePosition_Directommand[6] = val[2];
    changePosition_Directommand[5] = val[1];
    changePosition_Directommand[4] = val[0];


    // send commands
    changePosition_Direct(no);
  }

  else if (inC == 'M'){
    int inI = Serial.parseInt();

    setVelocity_Direct(no, inI);
  }

  else if (inC == 'Q'){
    if (tag == "a")
      responseRequested[0] = (Serial.read() == '1');
    else if (tag == "b")
      responseRequested[1] = (Serial.read() == '1');
    else if (tag == "c")
      responseRequested[2] = (Serial.read() == '1');

    if (responseRequested[0]) connectionerror[0] = 0;
    if (responseRequested[1]) connectionerror[1] = 0;
    if (responseRequested[2]) connectionerror[2] = 0;
  }
  else
    Serial.println("ERROR/void mismatch: input is -> " + inC);
}
