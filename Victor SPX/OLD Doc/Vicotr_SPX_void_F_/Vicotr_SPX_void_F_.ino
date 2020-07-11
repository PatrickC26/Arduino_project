//motor active list
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
  int ost=0; //over speed time

// ---------------------------------------------------------------
//void to activate the motor
  void motor (int power, float nowSpeed, float maxSpeed){
     
     //make sure value don't raise sharply
       String controller_stituation; //nor[normal];tqik[too_quickly];shr[sharply raise];eshr[extremly sharp raise]
        if ((power-lvSPX)<=8){
          controller_stituation="nor";
          vSPX=power;
        }
        else if ((power-lvSPX)<=16){
          controller_stituation="tqik";
          vSPX=power;
        }
        else if ((power-lvSPX)>=40){
          controller_stituation="eshr";
          vSPX=power;
        }
        else  controller_stituation="shr";

     //Let value be above 93
        if (vSPX<93) vSPX=93;
          
      //Tell the condition
        if(1){
          Serial.print("(");
          Serial.print(power);
          Serial.print(",");
          Serial.print(lvSPX);
          Serial.print(",");
          Serial.print(nowSpeed);
          Serial.print(",");
          Serial.print(maxSpeed);
          Serial.print(")");
          Serial.print("\t");
          Serial.print(controller_stituation);
          Serial.print("\t");
        }
        if (controller_stituation!="eshr"){
             /*if (vSPX<=5||(vSPX>=180&&vSPX<=598))
                  Serial.print("NON BREAK STOP");
             else if (vSPX>=6&&vSPX<=44)
                 Serial.print("MAX REVEERSE");
             else if (vSPX>=45&&vSPX<=90)
                 Serial.print("REVEERSE");*/
             if (vSPX>=91&&vSPX<=94)
                 Serial.print("BREAK STOPING");
             else if (vSPX>=95&&vSPX<=141)
                 Serial.print("FORWARD");
             else if (vSPX>=142&&vSPX<=179)
                 Serial.print("MAX FORWARD");
             Serial.print("\t");
        }
        else if (controller_stituation=="eshr") {
          if (ost==0){
             Serial.print("ERROR OCCUR  ");
             Serial.print("Please Turn Down the Controller  ");
             Serial.print("NON BREAK STOP  ");
             SPX.write(3);
             delay(100);
             SPX.write(94);
             lvSPX=vSPX=94;
             Serial.print("BREAK STOP  ");
          }
        }

      //STOP the motor
        if (vSPX>=91&&vSPX<=94){
          if (lvSPX==93||lvSPX==94){
            SPX.write(vSPX);
            Serial.println(vSPX);
          }
          else {
            Serial.print("3  ");
            SPX.write(3);
            delay(100);
            SPX.write(94);
            lvSPX=vSPX=94;
            Serial.print("94");
        }
        }

      //ACCELERATION NEGATIVE
        else if (vSPX<lvSPX){
           if(controller_stituation!="eshr"){
             for(int degree=lvSPX ; (vSPX<=degree&&(vSPX<=91||vSPX>=94)) ; degree--){
                Serial.print(degree);
                Serial.print(" ");
                SPX.write(degree);
                if (degree==95){
                  delay(50);
                }
                else if(controller_stituation=="nor")
                  delay(15);
                else if(controller_stituation=="tqik")
                  delay(10);
             }
           }
          Serial.println();
        }
        else if (vSPX==lvSPX){
          if (nowSpeed < maxSpeed){
            if (lvSPX!=93||lvSPX!=94)
              Serial.println(vSPX);
          }
        }

      //Speed under limited speed
        if (nowSpeed < maxSpeed){
        //ACCELERATION POSITIVE
          ost=0;
          if (vSPX>lvSPX){
            if(controller_stituation!="eshr"){
               for(int degree=lvSPX ; (vSPX>=degree&&(vSPX<=91||vSPX>=94)) ; degree++){
                Serial.print(degree);
                Serial.print(" ");
                SPX.write(degree);
                  if (degree==94){
                    delay(50);
                  }
                  else if(controller_stituation=="nor")
                    delay(15);
                  else if(controller_stituation=="tqik")
                    delay(10);
               }
             }
             Serial.println();
           }       
        }
        
        //Speed equal limited speed
        else if (nowSpeed==maxSpeed&&vSPX!=93&&vSPX!=94){
          if(vSPX>=lvSPX){
            vSPX=lvSPX;
            SPX.write(vSPX);
            Serial.println(vSPX);
            ost=1;
          }
        }
        
        //Speed over limited speed
        else if (nowSpeed > maxSpeed){
          if (vSPX>=lvSPX){
            if (vSPX>142){
              vSPX=142;
            }
            else if (vSPX<=142&&vSPX!=93&&vSPX!=94){
              //Serial.print(ost);
              Serial.print("\t");
              int check = nowSpeed-maxSpeed+0.5;
              vSPX =vSPX-check-ost*2;
              ost++;
              if (vSPX<93) vSPX=93;
              SPX.write(vSPX);
              Serial.println(vSPX);
              delay(100);
            }
          }
        }
     
     if (controller_stituation !="eshr"){
        lvSPX=vSPX;
   }
  }
  
  
//----------------------------------------------------------------------------------------
  void setup() {
    Serial.begin(9600);
    SPX.attach(A5);
    SPX.write(93);
    Serial.println("BREAK STOP");
  }


  void loop() {   
    // get value from computer
       int maxSpeed;
       if(1){
         while(Serial.available()){
           int valueFromComputer=Serial.parseInt();
           //TAKE "O" AWAY
           if (valueFromComputer!=0){
              Serial.print("Set MAX Speed to ");
              Serial.print(valueFromComputer);
              Serial.println("km/hr");
              maxSpeed=valueFromComputer;
           }
         }
       }
  
    //get value from analog[Speed,controller]
      if(1){

      // get value from controller [controller value]
         int valueFromController=analogRead(A0);
         int changedValueFromController = map(valueFromController,0,1023,93,145);
                   
      // get value for Speed
         int valueForSpeed=analogRead(A1);
         int changedValueForSpeed = map(valueForSpeed,0,1023,0,25);
      maxSpeed=20;
      // open motor loop
         motor(changedValueFromController,changedValueForSpeed,maxSpeed);
         delay(100);
      }
 }
