#include <SPI.h>
#include <MFRC522.h>     // 引用程式庫
#include <SoftwareSerial.h> 

#define RST_PIN   7        // 讀卡機的重置腳位
#define SS_PIN    10        // 晶片選擇腳位
#define redLED    9
#define greenLED  6
#define blueLED   5
byte UID[4];
//#define NEW_UID {0xEE, 0x5D, 0x86, 0xDD};

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance


MFRC522::MIFARE_Key key;
