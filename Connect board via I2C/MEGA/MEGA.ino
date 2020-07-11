#include <Wire.h>

const int SLAVE_ADDRESS = 3;
char incomingByte = 0;
String incomeString=" ",readString;
int ms ,lms= ms = 0;

void setup()
{
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  Serial.println("Received data");
  digitalWrite(8,1);
}

void loop(){
  ms=millis();
  if (ms >10000000){
    digitalWrite(8,0);
    delay(2000);
    pinMode(8,OUTPUT);
  }
  if (ms-lms>100&&incomeString!=" "){
    Serial.println(incomeString);
    int a =incomeString.toInt();
    String C=String(a);
    incomeString.replace(C," ");
    int b = incomeString.toInt();
    Serial.println(a);
    Serial.println(b);
    incomeString=" ";
    lms=ms;
  }
}

void receiveEvent(int howMany){
  while(Wire.available()){
    int a,b;
    incomingByte = Wire.read();
    //Serial.println(incomingByte);
    incomeString=incomeString+incomingByte;
  }
}
