void setup(){
    Serial.begin(9600);
    Serial.setTimeout(100);

//    setupTimer1();

    while( CAN.begin(CAN_125KBPS) ){   // init can bus : baudrate = 500k
        Serial.println("CAN BUS Shield init fail");
        Serial.println("Please Init CAN BUS Shield again");
        delay(100);
    }
//    Serial.println
    delay(100);


    for (int i = 0 ; i < 4 ; i ++){
      sendCommand(CAN_1, shutdown_command);
      sendCommand(CAN_2, shutdown_command);
      sendCommand(CAN_3, shutdown_command);
    }

}
