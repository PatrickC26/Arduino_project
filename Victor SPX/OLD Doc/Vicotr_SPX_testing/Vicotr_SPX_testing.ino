#include<Servo.h>

Servo SPX;
int vSPX=93;
int lvSPX=93 ; //Last value of vSPX

  void setup() {
    Serial.begin(9600);
    SPX.attach(A0);
    SPX.write(93);
    Serial.println("START");
    Serial.println("BREAK STOP");
  }

  void loop() {
  // get value from computer
  
      int a,b ;
      while(Serial.available()){
        a=Serial.parseInt();
        
        if (a!=0){
           b=a;
           Serial.println(b);
           if (b<180)
             vSPX=b;
        }
        
      }
  //get value from controller
  
    /*  int c=analogRead(A5);
      if(true){
        int d=c;
        vSPX=d;
        Serial.println(d);
        delay(100);
      }*/
  //make SPX move from vslue "vSPX"
    //~5 or 180~598    NON BREAK STOP
    //6~44             MAX REVERSE
    //45~90            REVERVE
    //91~94            BREAK　STOP
    //95~141           FORWARD
    //142~179          MAX FORWARD
      //Serial.print(vSPX);
      //Serial.println(lvSPX);

      if (lvSPX!=vSPX){
        //Tell the condition
        {if (vSPX<=5||(vSPX>=180&&vSPX<=598))
             Serial.println("NON BREAK STOP");
         else if (vSPX>=6&&vSPX<=44)
             Serial.println("MAX REVEERSE");
         else if (vSPX>=45&&vSPX<=90)
             Serial.println("REVEERSE");
         else if (vSPX>=91&&vSPX<=94)
             Serial.println("BREAK STOP");
         else if (vSPX>=95&&vSPX<=141)
             Serial.println("FORWARD");
         else if (vSPX>=142&&vSPX<=179)
             Serial.println("MAX FORWARD");}
             
         //Move the motor
         if (vSPX<=5){
           Serial.println(vSPX);
           SPX.write(vSPX);
           delay(1000);
           SPX.write(93);
           lvSPX=vSPX=93;
           Serial.println("BREAK STOP");
           
         }

         else if(vSPX>=91&&vSPX<=94){
           Serial.println(vSPX);
           SPX.write(vSPX);
           lvSPX=vSPX=93;
         }
         
         else if (vSPX<lvSPX){
           for(int degree=lvSPX ; vSPX<=degree ; degree--){
             Serial.print(degree);
             SPX.write(degree);
             delay(10);
           }
           Serial.println();
         }
         
         else if (vSPX>lvSPX){
           for(int degree=lvSPX ; degree<=vSPX ; degree++){
             Serial.print(degree);
             SPX.write(degree);
             delay(10);
           }
           Serial.println();
         }
         
         lvSPX=vSPX;
          
      }
  
  }
