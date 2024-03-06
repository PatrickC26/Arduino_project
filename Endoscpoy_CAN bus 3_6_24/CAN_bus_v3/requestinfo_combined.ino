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

void stop_Direct(int no){
  long2array(motor_position[no],changePosition_Directommand);
  int id = CAN_id[no];
  String tag = tagA[no];
  if ((!setPosition(id)) || (!enop(id)) || (!MA(id))) 
    Serial.println( tag + "ERROR/D: stop error");
}

void changePosition_Direct(int no){
  if (systemMode == modeName_disable){
    Serial.println("ERROR not init yet");
    return;
  }
  motor_final_position[no] = getFinalPosition(changePosition_Directommand);
  limitSensorStatus[no] = false;
  marginDetectStatus[no] = false;
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
  long2array(data,changePosition_Directommand);
  changePosition_Direct(no);
}




void changePosition_Direct_WaitUnitl(int no, long request_positon){
  make_array_indentical(changePosition_Directommand, request_positon);
  changePosition_Direct(no);

  Serial.println("getFinalPosition: " + String(getFinalPosition(changePosition_Directommand)));

  for(int i = 0 ; i< 500; i++){
    infoCheck();
    delay(10);
    if (motor_position[no] == getFinalPosition(changePosition_Directommand)) break;
    if (limitSensorStatus[no]) break;
  }
}


void changePosition_Relative_Direct_WaitUntil(int no, int moveDistance){
  long data = 0;

  changePosition_Relative_Direct(no, moveDistance);
  
  for (int i = 7 ; i >= 4 ; i--) {
    data += changePosition_Directommand[i] * _FF_pow[i-4];
  }

  Serial.println("motor_position: " + String(motor_position[no]));
  Serial.println("getFinalPosition: " + String(getFinalPosition(changePosition_Directommand)));
  Serial.println("data: " + String(data));
//  Serial.println("getFinalPosition: " + String(getFinalPosition));
  
//  data += moveDistance;
  
  for(int i = 0 ; i< 500; i++){
//    Serial.println("Target = " + String(data) + "current = " + String(motor_position[no]));
    infoCheck();
    delay(10);
    if (motor_position[no] == getFinalPosition(changePosition_Directommand)) break;
    if (limitSensorStatus[no]) break;
  }
}


void setVelocity_Direct(int no, int speedV){
  int id = CAN_id[no];
  String tag = tagA[no];
  unsigned char speedArray[8] ;
  long2array(speedV, speedArray);

  make_array_indentical(setVelocity_Directommand, speedArray);
  
  if (setVelocity(id))
    Serial.println(tag + "KM%");
  else 
    Serial.println(tag + "ERROR/M: setVelocity error");
}


void moveCalibration(int move2){ // front grasper close, rear grasper open
  changePosition_Direct_WaitUnitl(1, setPosition_rear_open);
  changePosition_Direct_WaitUnitl(0, setPosition_front_close);
  long2array(move2, changePosition_Directommand);
  changePosition_Direct_WaitUnitl(2, changePosition_Directommand);
}

void moveScope(int moveDistance){ // front grasper open, read grasper close
  changePosition_Direct_WaitUnitl(1, setPosition_rear_close);
  changePosition_Direct_WaitUnitl(0, setPosition_front_open);
  changePosition_Relative_Direct(2, -moveDistance);
}

void moveForward(int moveDistance){
  int pos = motor_position[2];
  int pos_final = pos + moveDistance;
  int pos_0 = motor_a_pos[2], pos_4 = motor_b_pos[2], pos_2 = (pos_0+pos_4)/2;
  int pos_1 = (pos_0+pos_2)/2, pos_3 = (pos_2+pos_4)/2;

  
  
  if (within(pos_3, pos_4, pos, 0) == within_a_b){
    if (within(pos_4, pos_4 + motor_max_distance[2]/4 , pos_final, 0) == within_a_b){
      //move to 2
      moveCalibration(pos_2);
//      changePosition_Direct_WaitUnitl(1, setPosition_rear_open);
//      changePosition_Direct_WaitUnitl(0, setPosition_front_close);
//      long2array(pos_2, changePosition_Directommand);
//      changePosition_Direct_WaitUnitl(2, changePosition_Directommand);
    }
    else if (within(pos_4, pos_4 + motor_max_distance[2]/4  , pos_final, 0) == within_b_side){
      //move to 0
      moveCalibration(pos_0);
//      changePosition_Direct_WaitUnitl(1, setPosition_rear_open);
//      changePosition_Direct_WaitUnitl(0, setPosition_front_close);
//      long2array(pos_0, changePosition_Directommand);
//      changePosition_Direct_WaitUnitl(2, changePosition_Directommand);
    }
    // move Forward
    moveScope(moveDistance);
//    changePosition_Direct_WaitUnitl(1, setPosition_rear_close);
//    changePosition_Direct_WaitUnitl(0, setPosition_front_open);
//    changePosition_Relative_Direct(2, -moveDistance);
  }
  else if (pos_final > pos_4){
    // move Forward
    int movedDistance = (pos_4-pos)
    moveScope(movedDistance);
    if ((moveDistance - movedDistance) > motor_max_distance[2]/4){
      moveCalibration(pos_1);
      moveForward(moveDistance - movedDistance);
    }
    else if ((moveDistance - movedDistance) > motor_max_distance[2]/2){
      moveCalibration(pos_0);
      moveForward(moveDistance - movedDistance);
    }
    else{
      moveCalibration(pos_2);
      moveForward(moveDistance - movedDistance);
    }
  }
  else{
    // move Forward
    moveScope(moveDistance);
//    changePosition_Direct_WaitUnitl(1, setPosition_rear_close);
//    changePosition_Direct_WaitUnitl(0, setPosition_front_open);
//    changePosition_Relative_Direct(2, -moveDistance);
  }
    
  

  // move Forward
  changePosition_Direct_WaitUnitl(1, setPosition_rear_close);
  changePosition_Direct_WaitUnitl(0, setPosition_front_open);
  changePosition_Relative_Direct(2, -moveDistance);

  if (within(pos_3, pos_4, motor_position[2], 0) == within_a_b){
    moveCalibration(pos_2);
    moveForward(0);
  }
  else if (within(pos_0, pos_1, motor_position[2], 0) == within_a_b){
    moveCalibration(pos_2);
    moveForward(0);
  }
  
}
