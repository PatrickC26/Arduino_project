#include "DFRobot_MCP2515.h"

const int SPI_CS_PIN = 10;

DFRobot_MCP2515 CAN(SPI_CS_PIN);


unsigned char position_request_data[8] = {0x40, 0x60, 0x60, 0x00, 0x01, 0x00, 0x00, 0x00};

unsigned char setPosition[8] = {0x23, 0x7A, 0x60, 0x00, 0x10, 0x27, 0x00, 0x00};
unsigned char data[8] = {0x2B, 0x40, 0x60, 0x00, 0x0F, 0x00, 0x00, 0x00};

unsigned char shutdown_data[8] = {0x2B, 0x40, 0x60, 0x00, 0x06, 0x00, 0x00, 0x00};
unsigned char switchon_data[8] = {0x2B, 0x40, 0x60, 0x00, 0x07, 0x00, 0x00, 0x00};
unsigned char enop_data[8] = {0x2B, 0x40, 0x60, 0x00, 0x0F, 0x00, 0x00, 0x00};

unsigned char MA_data[8] = {0x2B, 0x40, 0x60, 0x00, 0x3F, 0x00, 0x00, 0x00};


void setup()
{
    Serial.begin(9600);

    while( CAN.begin(CAN_125KBPS) ){   // init can bus : baudrate = 500k
        Serial.println("DFROBOT's CAN BUS Shield init fail");
        Serial.println("Please Init CAN BUS Shield again");
        delay(3000);
    }
    Serial.println("DFROBOT's CAN BUS Shield init ok!\n");


    delay(1000);

    Serial.println(CAN.sendMsgBuf(0x601, 0, 8, shutdown_data));
    delay(500);
    Serial.println(CAN.sendMsgBuf(0x601, 0, 8, switchon_data));
    delay(500);
    Serial.println(CAN.sendMsgBuf(0x601, 0, 8, enop_data));
    delay(500);


    Serial.println(CAN.sendMsgBuf(0x601, 0, 8, position_request_data));
    delay(500);
    Serial.println(CAN.sendMsgBuf(0x601, 0, 8, setPosition));
    delay(500);
    Serial.println(CAN.sendMsgBuf(0x601, 0, 8, enop_data));
    delay(500);
    Serial.println(CAN.sendMsgBuf(0x601, 0, 8, MA_data));
    delay(500);


    



}

unsigned char position_data[8] = {0x40, 0x64, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00};




void loop(){
    Serial.println(CAN.sendMsgBuf(0x601, 0, 8, position_data));
    delay(100);



    unsigned char len = 0;
    unsigned char buf[8];
    int ID= 0 ;

    if(CAN_MSGAVAIL == CAN.checkReceive()) {  // check if data coming
        Serial.println("INSIDE");
        CAN.readMsgBuf(&len, buf);   // read data,  len: data length, buf: data buf

        int id = CAN.getCanId();
        Serial.print(id,HEX);

        
        for(int i = 0; i<len; i++) {  // print the data
            Serial.print("\t");
            Serial.print(int(buf[i]), HEX);
            
        }
        Serial.println("\n");
    }
}
