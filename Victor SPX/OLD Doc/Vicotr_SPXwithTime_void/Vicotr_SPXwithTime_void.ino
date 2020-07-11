//motor list
    //make SPX move from vslue "vSPX"
    //~5 or 180~598    NON BREAK STOP
    //6~44             MAX REVERSE
    //45~90            REVERVE
    //91~94            BREAK　STOP
    //95~141           FORWARD
    //142~179          MAX FORWARD
//declare
  #include<Servo.h>
  Servo SPX;
  int vSPX=93;
  int lvSPX=93 ; //Last value of vSPX
  long getTime=0;
  bool suddenActiveSituation =0;
//

//void to activate the motor

  void motor (int b){
    
      if ((b-lvSPX)<=6){
        vSPX=b;
      }
      else {
        suddenActiveSituation=1;
        Serial.println("ERROR OCCUR");
        Serial.println("Please Turn Down the Controller");
        SPX.write(4);
      }

               


      if (lvSPX!=vSPX){
        //Tell the condition
         if(suddenActiveSituation==0){
                if (vSPX<=5/*||(vSPX>=180&&vSPX<=598)*/)
                Serial.print("NON BREAK STOP");
           else if (vSPX>=6&&vSPX<=44)
               Serial.print("MAX REVEERSE");
           else if (vSPX>=45&&vSPX<=90)
               Serial.print("REVEERSE");
           else if (vSPX>=91&&vSPX<=94)
               Serial.print("BREAK STOP");
           else if (vSPX>=95&&vSPX<=141)
               Serial.print("FORWARD");
           else if (vSPX>=142&&vSPX<=179)
               Serial.print("MAX FORWARD");
         }
         
             
        //Activate the motor
         if ((vSPX<=5)||(vSPX>=91&&vSPX<=94)){
           suddenActiveSituation=0;
           Serial.println("NON BREAK STOP");
           SPX.write(3);
           delay(3);
           SPX.write(94);
           lvSPX=vSPX=94;
           Serial.println("BREAK STOP");
         }
        
        //ACCELERATION NEGATIVE
         else if (vSPX<lvSPX){
            if(suddenActiveSituation==0){
               for(int degree=lvSPX ; (vSPX<=degree&&(vSPX<=91||vSPX>=94)) ; degree--){
                 Serial.print(degree);
                 SPX.write(degree);
                 delay(10);
               }
            }
           Serial.println();
         }
         //ACCELERATION POSITIVE
         else if (vSPX>lvSPX){
           if(suddenActiveSituation==0){
              for(int degree=lvSPX ; (vSPX>=degree&&(vSPX<=91||vSPX>=94)) ; degree++){
               Serial.print(degree);
               SPX.write(degree);
               delay(10);
             }
           }
           
           Serial.println();
         }         
         lvSPX=vSPX;         
      }
  }
  

  void setup() {
    Serial.begin(9600);
    SPX.attach(A5);
    SPX.write(93);
    Serial.println("BREAK STOP");
  }

  void loop() {
    
  // get value from computer
      while(Serial.available()){
         int valueFromComputer=Serial.parseInt();
         //TAKE "O" AWAY
         if (valueFromComputer!=0){
          motor(valueFromComputer);
         }
      }
  // get value from controller
      while(1){
        int valueFromController=analogRead(A0);
        //Serial.println(valueFromController);
        int valueFromVoid = map(valueFromController,0,1023,93,150);
        //Serial.println(valueFromVoid);
        motor(valueFromVoid);
      }
  }
         
