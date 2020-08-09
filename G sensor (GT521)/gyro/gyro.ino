#include<Wire.h>

const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ,fixX,fixY,fixZ;

int minVal=265;
int maxVal=402;

double x;
double y;
double z;

void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);
}

void serialEvent(){
  if (Serial.available()>0){
    char in = Serial.read();
    if (in=='R'){
      fixX=-x;
      fixY=-y;
      fixZ=-z;
    }
  }
}

void loop(){
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);
  AcX=Wire.read()<<8|Wire.read();
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();
  int xAng = map(AcX,minVal,maxVal,-90,90);
  int yAng = map(AcY,minVal,maxVal,-90,90);
  int zAng = map(AcZ,minVal,maxVal,-90,90);

  x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
  y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
  z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);

  x = x+fixX;
  y = y+fixY;
  z = z+fixZ;
  
  if (x<0) x+=360;
  if (y<0) y+=360;
  if (z<0) z+=360;

  Serial.print("AngleX= ");
  Serial.print(x);
  Serial.print("\t");
  Serial.println(AcX);
  
  Serial.print("AngleY= ");
  Serial.print(y);
  Serial.print("\t");
  Serial.println(AcY);
  
  Serial.print("AngleZ= ");
  Serial.print(z);
  Serial.print("\t");
  Serial.println(AcZ);
  Serial.println("-----------------------------------------");
  delay(400);
}
