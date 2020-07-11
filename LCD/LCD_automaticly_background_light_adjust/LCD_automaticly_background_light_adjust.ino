int r,lr;
void setup() {
Serial.begin(9600);
pinMode(12,OUTPUT);
pinMode(10,OUTPUT);
analogWrite(10,1023);
digitalWrite(12,1);

}

void loop() {
  // put your main code here, to run repeatedly:
  r=analogRead(A0);
  if(r!=lr){
    int a =map (r,100,1000,100,0);
   Serial.print(a);
   Serial.print("\t");
   int c =map (a,0,100,0,1023);
   if (c<500) c=500;
   Serial.println(c);
   analogWrite(10,c);
  }
  lr=r;
}
