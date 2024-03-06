void enable_C(int no){
  int id = CAN_id[no];
  String tag = tagA[no];
  if (!disable(id)) 
    Serial.println(tag + "ERROR/B: shutdown error%");
  else if (!switchon(id))
    Serial.println(tag + "ERROR/B: switchOn error%");
  else if (!enop(id))
    Serial.println(tag + "ERROR/B: enop error%");
  else
    Serial.println(tag + "KB%");
}

void disable_Direct(int no){
  int id = CAN_id[no];
  String tag = tagA[no];
  if (!disable(id)) 
    Serial.println(tag + "ERROR/C: shutdown error%");
  else 
    Serial.println(tag + "KC%");
}

void changePosition_Direct(int no){
  int id = CAN_id[no];
  String tag = tagA[no];
  if (!setPosition(id)) 
    Serial.println( tag + "ERROR/D: setPosition error");
  else if (!enop(id))
    Serial.println( tag + "ERROR/D: ENOP error");
  else if (!MA(id)) 
    Serial.println( tag + "ERROR/D: MA error");
  else
    Serial.println(tag + "KD%");
}

void changePosition_Relative_Direct(int no, int moveDistance){
  infoCheck();
  int id = CAN_id[no];
  String tag = tagA[no];
  long data = motor_position[no] + moveDistance;

  // set position
  if (data >= 0){
    for (int i = 7 ; i >= 4 ; i--) {
      changePosition_Directommand[i] = data / _FF_pow[i-4];
    }
  }
  else{
    data *= -1;
    for (int i = 7 ; i >= 4 ; i--) {
      changePosition_Directommand[i] = data / _FF_pow[i-4];
      changePosition_Directommand[i] = 0xFF - changePosition_Directommand[i];
    }
  }
  
  
  if (!setPosition(id)) 
    Serial.println( tag + "ERROR/D: setPosition error");
  else if (!enop(id))
    Serial.println( tag + "ERROR/D: ENOP error");
  else if (!MA(id)) 
    Serial.println( tag + "ERROR/D: MA error");
  else
    Serial.println(tag + "KD%");
}




void changePosition_Direct_WaitUnitl(int no, long request_positon){
  make_array_indentical(changePosition_Directommand, request_positon);
  changePosition_Direct(no);
  long data = 0;

  for (int i = 7 ; i >= 4 ; i--) {
    data += changePosition_Directommand[i] * _FF_pow[i-4];
  }

  for(int i = 0 ; i< 500 && motor_position[no] != data; i++){
//    Serial.println("Target = " + String(data) + "current = " + String(motor_position[no]));
    infoCheck();
    delay(10);
  }
}


void changePosition_Relative_Direct_WaitUntil(int no, int moveDistance){
  long data = 0;

  changePosition_Relative_Direct(no, moveDistance);
  
  for (int i = 7 ; i >= 4 ; i--) {
    data += changePosition_Directommand[i] * _FF_pow[i-4];
  }
  
//  data += moveDistance;
  
  for(int i = 0 ; i< 500 && motor_position[no] != data; i++){
//    Serial.println("Target = " + String(data) + "current = " + String(motor_position[no]));
    infoCheck();
    delay(10);
  }
}


void setVelocity_Direct(int no){
  int id = CAN_id[no];
  String tag = tagA[no];
  
  if (setVelocity(id))
    Serial.println(tag + "KM%");
  else 
    Serial.println(tag + "ERROR/M: setVelocity error");
}
