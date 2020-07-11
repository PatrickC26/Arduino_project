  int lv,av,v=av=lv=0;
  bool vo830=0;
  bool sit=0; // 0=slow , 1= fast
  bool st842;
  int v3,v4,v5,v6,v7,bv6,bv7=bv6=v3=v4=v5=v6=v7=0;

  
  void setup() {
    Serial.begin(9600);  
  }
  
  void loop() {
     av=v=analogRead(A0);
     int a = map(v,0,1000,0,10);
     if ((v-lv)>0){
       if(a==3)  v3++;
       if(a==4)  v4++;
       if(a==5)  v5++;
       if(a==6)  v6++;
       if(a==7)  v7++;
       int t=4;
       if(v3>t&&v4>t&&v4>t&&v5>t&&v6>t&&v7>t) sit =0;
       else if(v5>0 && v6>0 && v7>0) sit =1;
     }

     if ((v-lv)<0){
       if(a==6)  bv6++;
       if(a==7)  bv7++;
     }


     if (v<350){
       bv7=bv6=v3=v4=v5=v6=v7=0;
     }
     
     if (v>841||vo830){
       vo830=1;
       if (v==lv==842){}
       else if (v==842) vo830=0;
       if (vo830){
         if(!sit){
           if(v){
             v=830;
           }
         }
         if (sit){
           if (bv7<=1&&bv6<=2){
             v=830;
           }
         }
       }
     }
      Serial.print(v3);
      Serial.print("\t");
      Serial.print(v4);
      Serial.print("\t");
      Serial.print(v5);
      Serial.print("\t");
      Serial.print(v6);
      Serial.print("\t");
      Serial.print(v7);
      Serial.print("\t");
      Serial.print(bv6);
      Serial.print("\t");
      Serial.print(bv7);
      Serial.print("\t");
      Serial.print(vo830);
      Serial.print("\t");
      Serial.print(av);
      Serial.print("\t");
      Serial.println(v);
      lv=v;
  }
