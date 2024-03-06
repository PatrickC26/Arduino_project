void loop(){
  if (responseRequested_1){
    long pos = getPosition(CAN_1);
    Serial.println("aI" + String(pos) + "%");
    delay(5);
  
    long velocity = getVelocity(CAN_1);
    Serial.println("aL" + String(velocity) + "%");
    delay(5);

    long amp = getAmper(CAN_1);
    Serial.println("aH" + String(amp) + "%");
    delay(5);
  
    long temp = getTemperature(CAN_1);
    Serial.println("aJ" + String(temp) + "%");
    delay(5);
  }

  if (responseRequested_2){
    long pos = getPosition(CAN_2);
    Serial.println("bI" + String(pos) + "%");
    delay(5);
  
    long velocity = getVelocity(CAN_2);
    Serial.println("bL" + String(velocity) + "%");
    delay(5);

    long amp = getAmper(CAN_2);
    Serial.println("bH" + String(amp) + "%");
    delay(5);
  
    long temp = getTemperature(CAN_2);
    Serial.println("bJ" + String(temp) + "%");
    delay(5);
  }

  if (responseRequested_3){
    long pos = getPosition(CAN_3);
    Serial.println("cI" + String(pos) + "%");
    delay(5);
  
    long velocity = getVelocity(CAN_3);
    Serial.println("cL" + String(velocity) + "%");
    delay(5);

    long amp = getAmper(CAN_3);
    Serial.println("cH" + String(amp) + "%");
    delay(5);
  
    long temp = getTemperature(CAN_3);
    Serial.println("cJ" + String(temp) + "%");
    delay(5);
  }

  delay(100);
  

}
