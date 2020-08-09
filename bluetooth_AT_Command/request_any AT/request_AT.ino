#include <SoftwareSerial.h>
const int rxpin = 2; // 接收 pin
const int txpin = 3; // 發送 pin

int bluetoothStatus = 0;

SoftwareSerial Serial2(rxpin, txpin); // 建立虛擬序列埠

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
}

void loop() {
  String inS="";
  Serial2.println("AT+STATE");
  while (Serial2.available()<0);
    char in = Serial2.read();
    if (in=='+'){
      while(Serial2.available()){
        char iin = Serial2.read();
        inS += iin;
      }
    }
    inS.replace("OK","");
    inS.replace("\n","");
    inS.replace("STATE","");
    inS.replace(":","");
    inS.replace("=","");
    inS.replace(" ","");

  if (inS.length()>3){
    char a3 = inS[3];
    if (a3 =='T') bluetoothStatus = 0; //INITIALIZING
    else if (a3 =='D') bluetoothStatus = 1; //READY
    else if (a3 =='U') bluetoothStatus = 2; //INQUIRING 
    else if (a3 =='R') bluetoothStatus = 3; //PAIRABLE 
    else if (a3 =='N') {
      char a8 = inS[8];
      if (a8 =='N') bluetoothStatus = 4; //CONNECTING
      else if (a8 =='D') bluetoothStatus = 5; //CONNECTED
    }
  }
  else bluetoothStatus = inS.toInt();

}
