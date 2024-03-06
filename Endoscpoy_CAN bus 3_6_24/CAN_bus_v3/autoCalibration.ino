

void autoCalibration(int no, bool doSerial =false){
  if (systemMode == modeName_disable){
    Serial.println("ERROR not init yet");
    return;
  }
  int tempsystemMode = systemMode;
  systemMode = modeName_calibration;
  if(doSerial || doSerial_global)
    Serial.println("move back fast");
  setVelocity_Direct(no, velocity_calibration_fast);

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
  changePosition_Relative_Direct_WaitUntil(no, 0x500  * (motorCalibration_direction[no] ? -1 : 1));
  if(doSerial || doSerial_global)
    Serial.println("MOVED");

  if(doSerial || doSerial_global)
    Serial.println("move back slowly");
  setVelocity_Direct(no, velocity_calibration_slow);
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

  setVelocity_Direct(no, velocity_calibration_fast);

  changePosition_Relative_Direct_WaitUntil(no, 0x500* (motorCalibration_direction[no] ? -1 : 1));

  if (doSerial || doSerial_global)
    Serial.println("-------- DONE ----------");


  motor_a_pos[no] += 200* (motorCalibration_direction[no] ? -1 : 1);
  motor_b_pos[no] = motor_a_pos[no] + motor_max_distance[no]* (motorCalibration_direction[no] ? -1 : 1);
  
  

  systemMode = tempsystemMode;

}
