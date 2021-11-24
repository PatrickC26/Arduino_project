#include <SPI.h>
#include <MFRC522.h>     // 引用程式庫
#include <SoftwareSerial.h> 

#define RST_PIN   7        // 讀卡機的重置腳位
#define SS_PIN    10        // 晶片選擇腳位
#define redLED    9
#define greenLED  6
#define blueLED   5
#define BTH_RX    2
#define BTH_TX    3
int UID[4];
#define NEW_UID {0xEE, 0x5D, 0x86, 0xDD};

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance
SoftwareSerial BTH(BTH_RX,BTH_TX);

MFRC522::MIFARE_Key key;

void loop() {
  while(!BTH.available());
  while (BTH.available()){
    char in = BTH.read();
    if (in == 'R'){
      Serial.println("ENTER READING MODE");
      Serial.println(RFID_read());
    }
    else if (in == 'U'){
      String inS = "U";
      Serial.println("ENTER WTITTING MODE");
      while (inS.length()<23)  {
        delay(10);
        inS = inS + char(BTH.read());
      }
      Serial.println(inS);
      RFID_rewrite_UID(inS);
    }
  }
  

}
