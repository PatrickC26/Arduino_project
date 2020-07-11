#include <DHT.h>
#define dhtPin 8      //讀取DHT11 Data
#define dhtType DHT11 //選用DHT11   

DHT dht(dhtPin, dhtType); // Initialize DHT sensor

void setup() {
  Serial.begin(9600);//設定鮑率9600
  dht.begin();//啟動DHT
}

void loop() {
  float h = dht.readHumidity();//讀取濕度
  float t = dht.readTemperature();//讀取攝氏溫度
  float f = dht.readTemperature(true);//讀取華氏溫度
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Can't Read From DHT Sensor");
    return;
  }
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("%\t");
  Serial.print("Celsius: ");
  Serial.print(t);
  Serial.print("*C\t");
  Serial.print("Fahrenheit: ");
  Serial.print(f);
  Serial.print("*F\n");
  delay(1000);//延時5秒
}
