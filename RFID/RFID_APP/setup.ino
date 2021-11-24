void setup() {
  //pinModes
  pinMode(redLED,OUTPUT);
  pinMode(blueLED,OUTPUT);
  pinMode(greenLED,OUTPUT);
  //begin Serials
  Serial.begin(9600);
  BTH.begin(9600);
  analogWrite(redLED,10);  delay(400);
  //begin SPI
  SPI.begin();         // Init SPI bus
  digitalWrite(redLED,0);
  analogWrite(blueLED,10);  delay(400);
  //begin mfrc
  mfrc522.PCD_Init();  // Init MFRC522 card
  digitalWrite(blueLED,0);
  analogWrite(greenLED,10);  delay(400);  
  //begin key
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
  //ALL SET
  Serial.println("READY");
  digitalWrite(greenLED,0);
}
