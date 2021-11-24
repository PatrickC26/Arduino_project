void setup() {
  //begin screen
  screen.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Initialize display with the I2C address of 0x3C
  screen.clearDisplay();  // Clear the buffer
  screen.setTextColor(WHITE);
  
  //begin Serials
  Serial.begin(9600);
  Serial.setTimeout(100);
  
  //begin SPI
  SPI.begin();         // Init SPI bus
  
  //begin mfrc
  mfrc522.PCD_Init();  // Init MFRC522 card
  
  //begin key
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  Serial.println("Connect pin4 to Ground to activate Serial mode");
  pinMode(4,INPUT_PULLUP);
  delay(100);
  Serial.println(!digitalRead(4));
  if (digitalRead(4)){
    //ALL SET
    Serial.println("READY");
    screen.setFont(&FreeSans12pt7b);
    screen.setCursor(25, 40); // (x,y)
    screen.println("READY");
    screen.display();
    delay(500);
    screen.clearDisplay();
    screen.setCursor(25, 40); // (x,y)
    screen.println("      ");
    screen.display();
    delay(500);
    screen.setCursor(25, 40); // (x,y)
    screen.println("READY");
    screen.display();
    read();
  }
  else{
    screen.setFont(&FreeSans9pt7b);
    screen.setCursor(15, 40); // (x,y)
    screen.println("UART mode");
    screen.display();
    Serial.println("Please Enter a UID (4 UID only & Form should be correct) Ex:AA;3B;6C;FF;");
    int UIDno = 0;
    String intemp = "";
    while(!Serial.available()) ;
    while(Serial.available()){
      char in = Serial.read();
      if (in == ';'){
        char a[] ="   ";
        intemp.toCharArray(a,intemp.length()+1);
        int aback = StrtoHex(a);
        UID[UIDno] = aback;
        intemp = "";
        UIDno ++;
        if (UIDno == 4){
          screen.clearDisplay();
          screen.setFont(&FreeSans9pt7b);
          screen.setCursor(13, 40); // (x,y)
          screen.print(UID[0],HEX);
          screen.print(' ');
          screen.print(UID[1],HEX);
          screen.print(' ');
          screen.print(UID[2],HEX);
          screen.print(' ');
          screen.print(UID[3],HEX);
          screen.display();
          break;
        }
      }
      else if ((in>=48 && in<=57 ) || (in >= 65 && in <= 70)){
        intemp += in;
      }
      else{
        Serial.println("ERROR");
        screen.setFont(&FreeSans12pt7b);
        while (1){
          screen.setCursor(20, 40); // (x,y)
          screen.println("ERROR");
          screen.display();
          delay(500);
          screen.clearDisplay();
          screen.setCursor(20, 40); // (x,y)
          screen.println("      ");
          screen.display();
          delay(500);
        }
      }
      delay(10);
    }
  }
}

int StrtoHex(char str[]){
  return (int) strtol(str, 0, 16);
}

void loop(){
  if (UID[0]!=0&&UID[1]!=0&&UID[2]!=0&&UID[3]!=0)  write();
  else {
    Serial.println("ERROR");
    screen.setFont(&FreeSans12pt7b);
    while (1){
      screen.setCursor(20, 40); // (x,y)
      screen.println("ERROR");
      screen.display();
      delay(500);
      screen.clearDisplay();
      screen.setCursor(20, 40); // (x,y)
      screen.println("      ");
      screen.display();
      delay(500);
    }
  }
}
