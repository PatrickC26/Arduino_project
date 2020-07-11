void setup() { 
    Serial.begin(9600);
    Serial1.begin(9600); 
    Serial1.setTimeout(100);
 }


void loop() {
  while(Serial1.available()) {
    while('@' != Serial1.read()) { 
    }
    int n = Serial1.parseInt();
    Serial.println(n);
  }
  
}
   

             
