void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("START");
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(31, LOW); //31 echo pin
  delayMicroseconds(2);
  digitalWrite(31, HIGH);
  delayMicroseconds(10);
  digitalWrite(31, LOW);
    // 讀取 EchoPin LOW->HIGH->LOW 的這段時間是多少 us unsigned 
  long duration = pulseIn(30, HIGH); 
    // 換算成距離
  unsigned long distance = duration/58; 
  Serial.println(distance);
}
