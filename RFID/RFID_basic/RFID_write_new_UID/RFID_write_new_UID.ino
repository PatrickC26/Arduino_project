#include <SPI.h>
#include <MFRC522.h>
//#include <MFRC522Hack.h>

constexpr uint8_t RST_PIN = 8;
constexpr uint8_t SS_PIN = 9;

MFRC522 mfrc522(SS_PIN, RST_PIN);
//MFRC522Hack mfrc522Hack(&mfrc522);

byte newUid[] = {0xDE, 0xAD, 0xBE, 0xEF}; //預設UID
bool write_enable = false;
int wait_sec = 0;

MFRC522::MIFARE_Key key;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println(F("Warning: this example overwrites the UID of your UID changeable card, use with care!"));

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
}

void loop() {

  if(wait_sec>=0 && write_enable){
    wait_sec=wait_sec-1;
    delay(1000);
    if(wait_sec<2){
      tone(5, 466, 125);
    }
    if(wait_sec<=0){
      write_enable=false;
    }
  }

  // Look for new cards, and select one if present
  if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) {
    delay(50);
    return;
  }

  if(!write_enable){
    byte *id = mfrc522.uid.uidByte;
    byte idSize = mfrc522.uid.size;
    Serial.print("UID Size: ");
    Serial.println(idSize);
    if(idSize!=4){
      Serial.println(F("New UID is not 4 byte!"));
      return;
    }
    Serial.println(F("New UID set!"));

    for (byte i = 0; i < idSize; i++) {
      Serial.print("id[");
      Serial.print(i);
      Serial.print("]: ");
      newUid[i]=id[i];
      Serial.println(id[i], HEX);
    }
    Serial.println();
    mfrc522.PICC_HaltA();
    write_enable=true;
    wait_sec=10;
    tone(5, 740, 500);
    delay(50);
    return;
  }

  // Dump UID
  Serial.print(F("Card UID:"));
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.println();

  // Set new UID
//  if ( mfrc522Hack.MIFARE_SetUid(newUid, (byte)4, true) ) {
//    Serial.println(F("Wrote new UID to card."));
//  }

  // Halt PICC and re-select it so DumpToSerial doesn't get confused
  mfrc522.PICC_HaltA();
  if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) {
    return;
  }

  // Dump the new memory contents
  Serial.println(F("New UID and contents:"));
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  tone(5, 740, 250);
  delay(500);
  tone(5, 740, 250);
  write_enable = false;
  delay(2000);
}
