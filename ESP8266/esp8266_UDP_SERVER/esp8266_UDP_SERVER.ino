#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
  
// Set WiFi credentials
#define WIFI_SSID "AutoBrakeSetting"
#define WIFI_PASS "autobrakemsba"
#define UDP_PORT 4210
 
// UDP
WiFiUDP UDP;
char packet[255];
char reply[] = "Packet received!";
  
void setup() {
  // Setup serial port
  Serial.begin(9600);

  //Set up Wifi AP
  boolean result = ;
  if(WiFi.softAP(WIFI_SSID,WIFI_PASS))  Serial.println("Ready");
  else  Serial.println("Failed!");
 
  // Begin listening to UDP port
  UDP.begin(UDP_PORT);
  Serial.print("Listening on UDP port ");
  Serial.println(UDP_PORT);
  
}
 
void loop() {
 
  // If packet received...
  int packetSize = UDP.parsePacket();
  if (packetSize) {
    Serial.print("Received packet! Size: ");
    Serial.println(packetSize);
    int len = UDP.read(packet, 255);
    if (len > 0)
    {
      packet[len] = '\0';
    }
    Serial.print("Packet received: ");
    Serial.println(packet);
  }
 
}
Send a response
The last part of the code will send the response back to the sender. We must open the response with a UDP.beginPacket() method.

The first argument is the IP address we wish to send the packet to and the second argument is the port. We can use UDP.remoteIP() and UDP.remotePort() to use the values from the message sender.

We will then use UDP.write() to send the packet before ending with the UDP.endPacket() method.

1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41
42
43
44
45
46
47
48
49
50
51
52
53
54
55
56
57
58
59
60
61
62
63
64
65
66
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
  
// Set WiFi credentials
#define WIFI_SSID "Gysotc"
#define WIFI_PASS "ENPhaUr3gxEn"
#define UDP_PORT 4210
 
// UDP
WiFiUDP UDP;
char packet[255];
char reply[] = "Packet received!";
  
void setup() {
  // Setup serial port
  Serial.begin(115200);
  Serial.println();
  
  // Begin WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  
  // Connecting to WiFi...
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  // Loop continuously while WiFi is not connected
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  
  // Connected to WiFi
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
 
  // Begin listening to UDP port
  UDP.begin(UDP_PORT);
  Serial.print("Listening on UDP port ");
  Serial.println(UDP_PORT);
  
}
 
void loop() {
 
  // If packet received...
  int packetSize = UDP.parsePacket();
  if (packetSize) {
    Serial.print("Received packet! Size: ");
    Serial.println(packetSize);
    int len = UDP.read(packet, 255);
    if (len > 0)
    {
      packet[len] = '\0';
    }
    Serial.print("Packet received: ");
    Serial.println(packet);
 
    // Send return packet
    UDP.beginPacket(UDP.remoteIP(), UDP.remotePort());
    UDP.write(reply);
    UDP.endPacket();
 
  }
 
}
