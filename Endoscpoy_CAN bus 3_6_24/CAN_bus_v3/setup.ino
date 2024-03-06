void setup(){
  
  Serial.begin(115200);
  Serial.setTimeout(100);


  // initial Can bus
  while( CAN.begin(CAN_125KBPS) ){   // init can bus : baudrate = 500k
      Serial.println("CAN BUS Shield init fail");
      Serial.println("Please Init CAN BUS Shield again");
      delay(100);
  }
  delay(100);
  for (int i = 0 ; i < 4 ; i ++){
    for (int i = 0 ; i < 3 ; i ++)
      disable(CAN_id[i]);
  }


  // limit sensor initial
  for (int i = 0 ; i < 3 ; i++){
    pinMode(limitSensorPins[i], INPUT_PULLUP);
  }
  pinMode(limitSensorSignalPin, OUTPUT);
  digitalWrite(limitSensorSignalPin, 0);

  
  setupTimer1();

//  systemMode = modeName_disable;

}
