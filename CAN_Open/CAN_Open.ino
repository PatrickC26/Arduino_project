#include "DFRobot_MCP2515.h"

DFRobot_MCP2515 CAN(10);


unsigned char pos[8] = {0x40, 0x60, 0x60, 0x00, 0x01, 0x00, 0x00, 0x00};

unsigned char setPos[8] = {0x23, 0x7A, 0x60, 0x00, 0x10, 0x27, 0x00, 0x00};

unsigned char disable[8] = {0x2B, 0x40, 0x60, 0x00, 0x06, 0x00, 0x00, 0x00};
unsigned char enable[8] = {0x2B, 0x40, 0x60, 0x00, 0x07, 0x00, 0x00, 0x00};
unsigned char enop[8] = {0x2B, 0x40, 0x60, 0x00, 0x0F, 0x00, 0x00, 0x00};

unsigned char MA[8] = {0x2B, 0x40, 0x60, 0x00, 0x3F, 0x00, 0x00, 0x00};


void setup()
{
    Serial.begin(115200);

    while( CAN.begin(CAN_125KBPS) ){   // init can bus : baudrate = 500k
        Serial.println("DFROBOT's CAN BUS Shield init fail");
        Serial.println("Please Init CAN BUS Shield again");
        delay(3000);
    }
    Serial.println("DFROBOT's CAN BUS Shield init ok!\n");


    delay(1000);

    CAN.sendMsgBuf(0x601, 0, 8, disable);
    readData();
    delay(500);
    CAN.sendMsgBuf(0x601, 0, 8, enable);
    readData();
    delay(500);
    CAN.sendMsgBuf(0x601, 0, 8, enop);
    readData();
    delay(500);


    CAN.sendMsgBuf(0x601, 0, 8, pos);
    readData();
    delay(500);
    CAN.sendMsgBuf(0x601, 0, 8, setPos);
    readData();
    delay(500);
    CAN.sendMsgBuf(0x601, 0, 8, enop);
    readData();
    delay(500);
    CAN.sendMsgBuf(0x601, 0, 8, MA);
    readData();
    delay(500);


    



}

unsigned char position_data[8] = {0x40, 0x64, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00};




void loop(){
    CAN.sendMsgBuf(0x601, 0, 8, position_data);
    readData();
    delay(500);
}



void readData(){
  unsigned char len = 0;
  unsigned char buf[8];

  if(CAN_MSGAVAIL == CAN.checkReceive()) { 
      CAN.readMsgBuf(&len, buf);

      int id = CAN.getCanId();
      Serial.print(id,HEX);

      
      for(int i = 0; i<len; i++) {
          Serial.print("\t");
          Serial.print(int(buf[i]), HEX);
          
      }
      Serial.println("\n");
  }
}
