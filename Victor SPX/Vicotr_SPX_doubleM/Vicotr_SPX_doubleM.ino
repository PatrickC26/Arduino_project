/*//--------------------------motor active list-------------------------------------
   //make SPX move from vslue "SPXpower"
   //~5 or 180~598    NON BREAK STOP
   //6~44             MAX REVERSE
   //45~90            REVERVE
   //91~94            BREAK　STOP
   //95~141           FORWARD
   //142~179          MAX FORWARD */

//-------------------------------declare------------------------------------

#include<Servo.h>
Servo SPX1;
Servo SPX2;
int ASPXpower = 93; //Actual final power for SPX
int LASPXpower = 93; //Last actual final power for SPX
int LSPXpower = 93; //Last value of incame SPXpower
int ost = 0; //over speed time
int MBR = 30; //Motor Bound Rate
bool err = 0; //error accur
bool over145 = 0;

//------------------------------motor_void----------------------------------------------
void motor (int SPXpower, float nowSpeed, float maxSpeed, bool brake) {
  String htc; //how motor value change

  //make sure value don't raise sharply by accident & Let value be above 93
  if ((SPXpower - LSPXpower) >= 90 || SPXpower < 93) err = 1;

  //Tell the condition if error occur
  if (err) {
    Serial.print("ERROR OCCUR  ");
    Serial.print("Please Turn Down the Controller  ");
    Serial.print("NON BREAK STOP  ");
    SPX(3);
    delay(MBR);
    SPX(94);
    ASPXpower = 94;
    Serial.println("BREAK STOP  ");
  }

  //Activate the motor
  //STOP the motor
  if ((SPXpower == 93 || SPXpower == 94) && (LASPXpower == 93 || LASPXpower == 94)) {
    ASPXpower = SPXpower;
    SPX(ASPXpower);
    err = 0;
  }
  else if ((SPXpower == 93 || SPXpower == 94) && (LASPXpower != 93 && LASPXpower != 94)) {
    SPX(3);
    delay(MBR);
    ASPXpower = SPXpower;
    SPX(ASPXpower);
  }
  else if (brake == 1) {
    if (LASPXpower != 93 && LASPXpower != 94) {
      SPX(3);
      delay(300);
      htc += "3 ";
    }
    SPX(94);
    ASPXpower = 94;
    htc += "94";
  }

  //ACCELERATION NEGATIVE
  else if (SPXpower < LASPXpower) {
    if (!err) {
      for (int degree = LASPXpower ; (SPXpower <= degree && (SPXpower >= 94)) ; degree--) {
        htc = htc + degree + "　";
        SPX(degree);
        if (degree == 95) delay(50);
        else delay (MBR);
        ASPXpower = degree;
      }
    }
  }

  //Speed under limited speed
  if (nowSpeed < maxSpeed) {
    //ACCELERATION POSITIVE
    ost = 0;
    if (SPXpower > LASPXpower && !err && !brake) {
      for (int degree = LASPXpower ; (SPXpower >= degree && (SPXpower >= 94)) ; degree++) {
        htc = htc + degree + "　";
        SPX(degree);
        if (degree == 94) delay(50);
        else delay (MBR);
        ASPXpower = degree;
      }
    }
  }

  //Speed equal limited speed
  else if (nowSpeed == maxSpeed && SPXpower != 93 && SPXpower != 94) {
    if (SPXpower >= LASPXpower) {
      ASPXpower = LASPXpower;
      SPX(ASPXpower);
      ost = 1;
    }
  }

  //Speed over limited speed
  else if (nowSpeed > maxSpeed) {
    if (SPXpower >= LASPXpower) {
      if (SPXpower != 93 && SPXpower != 94) {
        int check = nowSpeed - maxSpeed + 0.5;
        ASPXpower = SPXpower - check * 2 - ost * 2;
        if (ASPXpower > LASPXpower) {
          ASPXpower = LASPXpower;
        }
        ost++;
        if (ASPXpower < 93) ASPXpower = 93;
        SPX(ASPXpower);
        htc = htc + ASPXpower + ost + "'";
        delay(100);
      }
    }
  }

  //Tell the condition
  if (SPXpower != LSPXpower || ASPXpower != LASPXpower) {
    Serial.print("(");
    Serial.print(SPXpower);
    Serial.print(",");
    Serial.print(LSPXpower);
    Serial.print(",");
    Serial.print(ASPXpower);
    Serial.print(",");
    Serial.print(LASPXpower);
    Serial.print(",");
    Serial.print(nowSpeed);
    Serial.print(",");
    Serial.print(maxSpeed);
    Serial.print(",");
    Serial.print(brake);
    Serial.print(")");
    Serial.print("\t");
    if ((ASPXpower == 93 || ASPXpower == 94) && (LASPXpower == 93 || LASPXpower == 94))
      Serial.print("BREAK STOPPED ");
    else if (((ASPXpower == 93 || ASPXpower == 94) && (LASPXpower != 93 && LASPXpower != 94)))
      Serial.print("BREAK STOPPING");
    else if (ASPXpower >= 95 && ASPXpower <= 141)
      Serial.print("FORWARD    ");
    else if (ASPXpower >= 142 && ASPXpower <= 179)
      Serial.print("MAX FORWARD");
    Serial.println(htc);
  }

  //Make value of LASPXpower & LSPXpower
  LASPXpower = ASPXpower;
  LSPXpower = SPXpower;

}


//------------------------------SPX_void----------------------------------------------
void SPX(int power) {
  SPX1.write(power);
  SPX2.write(power);
}

//------------------------------battery----------------------------------------
void battery(int vol) {
  vol = map(vol, 0, 1023, 0, 500);
  Serial.println(vol * 3);
}


//------------------------------setup----------------------------------------------
void setup() {
  Serial.begin(9600);
  SPX1.attach(A7);
  SPX2.attach(A8);
  SPX(93);
  Serial.println("BREAK STOP");
  int valueFromController = analogRead(A0);
  int changedValueFromController = map(valueFromController, 195, 800, 93, 145);
  if (changedValueFromController > 94) err = 1;
  SPX(100);
  SPX(4);
  SPX(93);
}


//------------------------------loop----------------------------------------------
void loop() {
  // get value from computer
  int maxSpeed;
  battery(analogRead(A1));
  //----------computer value in --------------------
  if (1) {
    while (Serial.available()) {
      int valueFromComputer = Serial.parseInt();
      //TAKE "O" AWAY
      if (valueFromComputer != 0) {
        Serial.print("Set MAX Speed to ");
        Serial.print(valueFromComputer);
        Serial.println("km/hr");
        maxSpeed = valueFromComputer;
      }
    }
  }
  //-----------controller value in----------------

  //get value from analog[Speed,controller]
  if (1) {

    // get value from controller [controller value]
    int valueFromController = analogRead(A0);
    int changedValueFromController = map(valueFromController, 0, 1023, 93, 145);

    // get value for Speed  [controller speed]
    int valueForSpeed = analogRead(A1);
    int changedValueForSpeed = map(valueForSpeed, 0, 1023, 0, 25);
    changedValueForSpeed = 0;
    maxSpeed = 20;

    //get value for brake   [cotroller brake]
    bool brake = digitalRead(10);

    // open motor loop
    motor(changedValueFromController, changedValueForSpeed, maxSpeed, brake);
  }
  delay(100);

}
