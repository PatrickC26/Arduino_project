#include <SPI.h>
#include <MFRC522.h>     // 引用程式庫
#include <Adafruit_SSD1306.h> 
#include <Fonts/FreeSans9pt7b.h>  // Add a custom font
#include <Fonts/FreeSans12pt7b.h>  // Add a custom font

Adafruit_SSD1306 screen(128, 64); 

#define RST_PIN   10        // 讀卡機的重置腳位
#define SS_PIN    A0         // 晶片選擇腳位

byte UID[4];
bool state = false; //false -> read  true -> write
//#define NEW_UID {0xEE, 0x5D, 0x86, 0xDD};

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance


MFRC522::MIFARE_Key key;
