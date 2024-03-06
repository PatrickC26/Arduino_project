const bool motorCalibration_direction[3] = {0,1,1}; // 0 -> move negative ; 1 -> move positive toward the limit sensor

void autoCalibration(int no, bool doSerial =false){
  int tempMode = mode;
  mode = modeName_calibration;
  if(doSerial || doSerial_global)
    Serial.println("move back fast");
  make_array_indentical(setVelocity_Directommand, velocity_calibration_fast);
  setVelocity_Direct(no);

//  Serial.println("motorCalibration_direction: " + String((motorCalibration_direction[no] ? 1 : -1)));
  changePosition_Relative_Direct(no, 0x1000 * (motorCalibration_direction[no] ? 1 : -1));
  
  if(doSerial || doSerial_global)
    Serial.println("waiting to be touched");
  while (true){
    infoCheck();
    if (digitalRead(limitSensorPins[no])) {
      break;
    }
  }

  if (doSerial || doSerial_global)
    Serial.println("move front a little");
//  Serial.println("motorCalibration_direction: " + String((motorCalibration_direction[no] ? -1 : 1)));
  changePosition_Relative_Direct_WaitUntil(no, 0x300  * (motorCalibration_direction[no] ? -1 : 1));
  if(doSerial || doSerial_global)
    Serial.println("MOVED");

  if(doSerial || doSerial_global)
    Serial.println("move back slowly");
  make_array_indentical(setVelocity_Directommand, velocity_calibration_slow);
  setVelocity_Direct(no);
  changePosition_Relative_Direct(no, 0x1000  * (motorCalibration_direction[no] ? 1 : -1));

  
  if(doSerial || doSerial_global)
    Serial.println("waiting to be touched");
  while (true){
    infoCheck();
    if (digitalRead(limitSensorPins[no])) {
      motor_a_pos[no] = motor_position[no];
      break;
    }
  }
  changePosition_Relative_Direct(no, 0);

  if(doSerial || doSerial_global)
    Serial.println(motor_position[no]);

  changePosition_Relative_Direct(no, 0x300* (motorCalibration_direction[no] ? -1 : 1));

  if (doSerial || doSerial_global)
    Serial.println("-------- DONE ----------");


  motor_a_pos[no] += 500* (motorCalibration_direction[no] ? -1 : 1);
  motor_b_pos[no] = motor_a_pos[no] + motor_max_distance[no]* (motorCalibration_direction[no] ? -1 : 1);
    

  mode = tempMode;

}
