void setupTimer1() {  // Timer 1 setup
  cli(); // Disable interrupts
  
  // Set Timer 1 to CTC (Clear Timer on Compare Match) mode
  TCCR1A = 0; // Set Timer 1 Control Register A to 0
  TCCR1B = 0; // Set Timer 1 Control Register B to 0
  
  OCR1A = 7812; // (16MHz / 1024) * 0.5 - 1 = 7812

  TCCR1B |= (1 << WGM12);  // turn on CTC mode
  
  TCCR1B |= (1 << CS12) | (1 << CS10);  // Configure Timer 1 prescaler to 1024
  
  TIMSK1 |= (1 << OCIE1A);  // Enable Timer 1 compare match interrupt
  
  sei(); // Enable interrupts
}


ISR(TIMER1_COMPA_vect) {
  sendInfo();
}


void sendInfo(){
  for (int i = 0 ; i < 3 ; i++){
    if (responseRequested[i]){
      Serial.println(tagA[i] + "I" + String(motor_position[i]) + "%");
      Serial.println(tagA[i] + "L" + String(motor_velocity[i]) + "%");
      Serial.println(tagA[i] + "H" + String(motor_current[i]) + "%");
      Serial.println(tagA[i] + "J" + String(motor_temperature[i]) + "%");
    }
  }

  for (int i = 0 ; i < 3 ; i ++){
    Serial.print(limitSensorStatus[i]);
    Serial.print("\t");
  }
  Serial.println();
}
