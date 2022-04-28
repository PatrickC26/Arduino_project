//FirebaseESP8266.h must be included before ESP8266WiFi.h
#include "FirebaseESP8266.h"
//#include <LineNotifyESP8266.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>


// 設定網路SSID跟密碼
#define WIFI_SSID "AutoBrake"
#define WIFI_PASSWORD "nlhs7626"

//設定Line Notify
#define LINE_TOKEN "dQTTxukM2YZej9SttKNZrffr2XJYcnhpkOjopF3p4Dd"

void setup() {
  Serial.begin(9600);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }

}


void loop() {
//
//    String Send = "";
//    Send = "TEST" ;
//    LineNotifyHTTPClient net;
//    lineNotify.init(&net, LINE_TOKEN);
//
//    uint8_t status;
//
//    status = lineNotify.sendLineMessage(Send);
//    if (status == LineNotifyESP8266::LineStatus::SENT_COMPLETED)
//    {
//      Serial.println("Send text message completed");
//      Serial.println("Text message limit: " + String(lineNotify.textMessageLimit()));
//      Serial.println("Text message remaining: " + String(lineNotify.textMessageRemaining()));
//      Serial.println("Image message limit: " + String(lineNotify.imageMessageLimit()));
//      Serial.println("Image message remaining: " + String(lineNotify.imageMessageRemaining()));
//    }
//    else if (status == LineNotifyESP8266::LineStatus::SENT_FAILED)
//      Serial.println("Send text message was failed!");
//    else if (status == LineNotifyESP8266::LineStatus::CONNECTION_FAILED)
//      Serial.println("Connection to LINE sevice faild!");
//    else if (status == LineNotifyESP8266::LineStatus::NOT_INITIALIZED)
//      Serial.println("Line notify was not initialized!");
//    Serial.println();
//
//
//
//    lineNotify.end();
}
