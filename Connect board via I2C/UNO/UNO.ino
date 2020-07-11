#include <Wire.h>

const int SLAVE_ADDRESS = 3;
char incomingByte = 0;

void setup()
{ 
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Type something to send");
} 

void loop()
{
}

void serialEvent()
{ 
  incomingByte = Serial.read();
  
  Wire.beginTransmission(SLAVE_ADDRESS); 
  Wire.write(incomingByte);
  Wire.endTransmission();
}
