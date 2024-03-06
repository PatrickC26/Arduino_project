void limitSensorCheck(){
  // limit sensor
  for (int i = 0 ; i < 3 ; i ++){
    limitSensorStatus_pre[i] = limitSensorStatus[i];
    limitSensorStatus[i] = digitalRead(limitSensorPins[i]);
    if (limitSensorStatus[i] && !limitSensorStatus_pre[i]){
//      disable_Direct(i);
//      enable_C(i);
      Serial.println("motor " + tagA[i] + " TOUCHED");
      changePosition_Relative_Direct(i,0);
    }
  }
}


void currentCheck(){
  if (motor_current[0] > 100){
    Serial.println("OVERCURRENT_1");
  }

  if (motor_current[1] > 100){
    Serial.println("OVERCURRENT_2");
  }

  if (motor_current[2] > 100){
    Serial.println("OVERCURRENT_3");
  }

}


void marginCheck(){
  for (int i = 0 ; i < 3 ; i ++){
    if (motor_a_pos[i] > motor_b_pos[i]){
      if (motor_position[i] > motor_a_pos[i]){
        changePosition_Relative_Direct(i,0);
      }
      if (motor_position[i] < motor_b_pos[i]){
        changePosition_Relative_Direct(i,0);
      }
    }
  
    if (motor_a_pos[i] < motor_b_pos[i]){
      if (motor_position[i] < motor_a_pos[i]){
        changePosition_Relative_Direct(i,0);
      }
      if (motor_position[i] > motor_b_pos[i]){
        changePosition_Relative_Direct(i,0);
      }
    }
  }
}


void infoCheck(){
  // CAN
  for (int i = 0 ; i < 3 ; i++){
    if (connectionerror > 20){
      if (connectionStatus[i]){
        motor_position[i] = getPosition(CAN_id[i]);
        motor_velocity[i] = getVelocity(CAN_id[i]);
        motor_current[i] = getAmper(CAN_id[i]);
        motor_temperature[i] = getTemperature(CAN_id[i]);

        if ((motor_position[i] == 0xF0000000)||(motor_velocity[i] == 0xF0000000)||(motor_current[i] == 0xF0000000)||(motor_temperature[i] == 0xF0000000)){
          connectionerror[i] ++;
          CAN.begin(CAN_125KBPS);
        }
        
      }
      else{
        String serialNo = getSerialNo(CAN_id[i]);
        if (serialNo.indexOf("-") >= 0){
          CAN.begin(CAN_125KBPS);
          connectionerror[i] ++;
        }
        else {
          responseRequested[i] = true;
          connectionStatus[i] = 1;
          connectionerror[i] = 0;
        }
      }
      if (connectionerror[i] > 5) responseRequested[i] = false;
    }
    limitSensorCheck();
    if (mode != modeName_calibration)
      marginCheck();
  }


    


}


void loop(){
  infoCheck();
  
  
  delay(5);
  

}
