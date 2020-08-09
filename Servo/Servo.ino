#include<Servo.h>

Servo brake;

void setup() {
  // put your setup code here, to run once:
brake.attach(9);
brake.write(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()){
    int in = Serial.parseInt();
    Serial.println(in);
    brake.write(in);
  }
}
