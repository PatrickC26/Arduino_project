#include <Stepper.h>

#define STEPS 32

Stepper stepper(STEPS, 8, 10, 9, 11);

void setup() {  
  Serial.begin(9600);
  Serial.println("BEGIN");
  
}

void loop() {
  stepper.setSpeed(500); //2~500
  stepper.step(1000); //1or-1
}
