void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial2.begin(9600);
  Serial.print("\nbegin");
  int A = 85;
  int B = 5;
  int C = 0;
  int D = 0;
  int E = 0;
  int F = 0;
  int G = 204;
  int H = 170;
  
//  for (int i = 0; i<14;i++){
//    Serial2.write(B[i]);
//    Serial.write(B[i]);
//  }
  Serial.print(A);
  Serial2.print(A,HEX);
  Serial.print(B);
  Serial2.print(B,HEX);
  Serial.print(C);
  Serial2.print(C,HEX);
  Serial.print(D);
  Serial2.print(D,HEX);
  Serial.print(E);
  Serial2.print(E,HEX);
  Serial.print(F);
  Serial2.print(F,HEX);
  Serial.print(G);
  Serial2.print(G,HEX);
  Serial.print(H);
  Serial2.print(H,HEX);
}

void loop() {
while (Serial.available()){
  char in = (Serial.read());
  Serial.print(in);
  Serial2.print(in);
}
while (Serial2.available()){
//  char in = Serial2.read();
  Serial.print(Serial2.read());
}
delay(300);
Serial.println();
}
