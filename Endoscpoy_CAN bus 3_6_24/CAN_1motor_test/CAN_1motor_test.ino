const unsigned char modes_of_operation[8] = {0x40, 0x60, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00};
// 4F 60  60  0 1 0 0 0
// 4F 60  60  0 3 0 0 0
const unsigned char position_mode_command[8] = {0x2F, 0x60, 0x60, 0x00, 0x01, 0x00, 0x00, 0x00};
// 60 60  60  0 0 0 0 0
const unsigned char velocity_mode_command[8] = {0x2F, 0x60, 0x60, 0x00, 0x03, 0x00, 0x00, 0x00};
// 60 60  60  0 0 0 0 0
const unsigned char modes_reply_OK_command[4] = {0x60, 0x60, 0x60, 0x0};



const unsigned char get_serialNo_command[8] = {0x40, 0x18, 0x10, 0x04, 0x0, 0x0, 0x0, 0x0};
// 43 18  10  4 88  A4  0 F
// 43 18  10  4 7D  A4  0 F
// 43 18  10  4 79  A4  0 F
// 43 18  10  4 78  A4  0 F
// ----void----______id_____
const unsigned char serialNo_reply_OK_command[4] = {0x43, 0x18, 0x10, 0x04};


// control word
const unsigned char shutdown_command[8] = {0x2B, 0x40, 0x60, 0x00, 0x06, 0x00, 0x00, 0x00};
// 581 60  40  60  0 0 0 0 0
const unsigned char switchon_command[8] = {0x2B, 0x40, 0x60, 0x00, 0x07, 0x00, 0x00, 0x00};
// 581 60  40  60  0 0 0 0 0
const unsigned char enop_command[8] = {0x2B, 0x40, 0x60, 0x00, 0x0F, 0x00, 0x00, 0x00};
// 581  60  40  60  0 0 0 0 0
const unsigned char MA_command[8] = {0x2B, 0x40, 0x60, 0x00, 0x3F, 0x00, 0x00, 0x00};
// 581 60  40  60  0 0 0 0 0
const unsigned char controlWord_reply_OK_command[4] = {0x60, 0x40, 0x60, 0x0};


unsigned char setPosition[8] = {0x23, 0x7A, 0x60, 0x00, 0x10, 0x17, 0x00, 0x00};
// 581 60  7A  60  0 0 0 0 0
const unsigned char setPosition_reply_OK_command[4] = {0x60, 0x7A, 0x60, 0x0};

// Check
unsigned char setVelocity[8] = {0x23, 0x7F, 0x60, 0x00, 0x10, 0x07, 0x00, 0x00};
// 60 7F  60  0 0 0 0 0
const unsigned char setVelocity_reply_OK_command[4] = {0x60, 0x7F, 0x60, 0x0};


unsigned char get_velocity_command[8] = {0x40, 0x6C, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00};
// 43  6C  60  0 FF  FF  FF  FF
const unsigned char getVelocity_reply_OK_command[4] = {0x43, 0x6C, 0x60, 0x0};


unsigned char get_position_command[8] = {0x40, 0x64, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00};
// 43  64  60  0 10  37  0 0
const unsigned char getPosition_reply_OK_command[4] = {0x43, 0x64, 0x60, 0x0};

// Double-Check
unsigned char get_amper_command[8] = {0x40, 0x78, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00};
// 581  4B  78  60  0 2F  0 0 0
const unsigned char getAmper_reply_OK_command[4] = {0x4B, 0x78, 0x60, 0x0};

// Double-Check
unsigned char get_temp_command[8] = {0x40, 0x23, 0x23, 0x02, 0x00, 0x00, 0x00, 0x00};
// 4B 23  23  2 27  0 0 0
const unsigned char getTemp_reply_OK_command[4] = {0x4B, 0x23, 0x23, 0x2};




#include "DFRobot_MCP2515.h"

const int SPI_CS_PIN = 10;

DFRobot_MCP2515 CAN(SPI_CS_PIN);

int id = 0x604;

void setup(){
    Serial.begin(9600);
    Serial.setTimeout(100);

//    setupTimer1();

    while( CAN.begin(CAN_125KBPS) ){   // init can bus : baudrate = 500k
        Serial.println("CAN BUS Shield init fail");
        Serial.println("Please Init CAN BUS Shield again");
        delay(100);
    }
    Serial.println("CAN BUS Shield init OK");
//    Serial.println
    delay(100);


    for (int i = 0 ; i < 4 ; i ++){
      CAN.sendMsgBuf(id, 0, 8, shutdown_command);
      delay(5);
      checkResponse_reply();
    }


    Serial.println("shutdown_command");
    CAN.sendMsgBuf(id, 0, 8, shutdown_command);
    delay(5);
    checkResponse_reply();


    

    // Press any key to resume
    while(!Serial.available());
    while(Serial.available()){
      Serial.read();
    }


    

    Serial.println("switchon_command");
    CAN.sendMsgBuf(id, 0, 8, switchon_command);
    delay(5);
    checkResponse_reply();

    Serial.println("enop_command");
    CAN.sendMsgBuf(id, 0, 8, enop_command);
    delay(5);
    checkResponse_reply();


    // Press any key to resume
    while(!Serial.available());
    while(Serial.available()){
      Serial.read();
    }


    Serial.println("setposition_command");
    CAN.sendMsgBuf(id, 0, 8, setPosition);
    delay(5);
    checkResponse_reply();

    Serial.println("enop_command");
    CAN.sendMsgBuf(id, 0, 8, enop_command);
    delay(5);
    checkResponse_reply();

    Serial.println("MA_command");
    CAN.sendMsgBuf(id, 0, 8, MA_command);
    delay(5);
    checkResponse_reply();
    
}

void checkResponse_reply(){
  unsigned char len = 0;
  unsigned char buf[8];
  
  for (int i = 0 ; i < 5 ; i++){
    if(CAN_MSGAVAIL == CAN.checkReceive()) {  // check if data coming
//      Serial.println("INSIDE");
      CAN.readMsgBuf(&len, buf);   // read data,  len: data length, buf: data buf
      int id = CAN.getCanId();

      Serial.print(id, HEX);
      
      for(int i = 0; i<len; i++) {  // print the data
          Serial.print("\t");
          Serial.print(int(buf[i]), HEX);
      }
      Serial.println("\n");
      break;
    }
  }
}

void loop() {
  
}
