#include "DFRobot_MCP2515.h"

const int SPI_CS_PIN = 10;

DFRobot_MCP2515 CAN(SPI_CS_PIN);

#define debug true

const int CAN_id[3] = {0x602,0x603,0x604};
long motor_position[3] = {0,0,0};
long motor_velocity[3] = {0,0,0};
long motor_current[3] = {0,0,0};
long motor_temperature[3] = {0,0,0};

long motor_a_pos[3] = {0,0,0};
long motor_b_pos[3] = {0,0,0};
int motor_max_distance[3] = {1252,2904,0x2028};

const char limitSensorPins[3] = {5,4,3};
const char limitSensorSignalPin = A5;
bool limitSensorStatus[3] = {0,0,0};
bool limitSensorStatus_pre[3] = {0,0,0};

//const long _FF_pow[4] = {1, 256, 65536, 16777216};
const long _F_pow[8] = {1, 16, 256, 4096, 65536, 1048576, 16777216, 268435456};
const long _FF_pow[4] = {_F_pow[0], _F_pow[2], _F_pow[4], _F_pow[6]};

bool responseRequested[3] = {0,0,1};
bool connectionStatus[3] = {0,0,0};
int connectionerror[3] = {0,0,0};

bool doSerial_global = false;

byte mode = 0;
const byte modeName_disable = 0;
const byte modeName_calibration = 1;
const byte modeName_engineering = 2;
const byte modeName_user = 3;

String tagA[3] = {"a","b","c"};
