#include "DFRobot_MCP2515.h"

const int SPI_CS_PIN = 10;

DFRobot_MCP2515 CAN(SPI_CS_PIN);

#define debug true

#define CAN_1 0x602
#define CAN_2 0x603
#define CAN_3 0x604


//const long _FF_pow[4] = {1, 256, 65536, 16777216};
const long _F_pow[8] = {1, 16, 256, 4096, 65536, 1048576, 16777216, 268435456};
const long _FF_pow[4] = {_F_pow[0], _F_pow[2], _F_pow[4], _F_pow[6]};


bool responseRequested_1 = true;
bool responseRequested_2 = false;
bool responseRequested_3 = false;


bool connectionStatus_1 = false;
bool connectionStatus_2 = false;
bool connectionStatus_3 = false;


int connectionerror_1 = 0;
int connectionerror_2 = 0;
int connectionerror_3 = 0;
