#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

const char* months[] = {"January", "February", "March", "April", "May", "June", "July", "August","September", "October", "November", "December"};


DateTime tt;  //variable of type DateTime


void setup () {

  Serial.begin(9600);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);   // sketch halts in an endless loop
  }
  
  
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
  
    //set the RTC date & time - to the time this sketch was compiled
//    rtc.adjust(DateTime(__DATE__, __TIME__));
 
    // set the RTC date & time - to any time you choose example 
//     rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));      // would set to January 21, 2014 at 3:00:00 (3am)
     
  }
  
  //get time 
  tt = rtc.now();
  
  //get temperature 
  float c = rtc.getTemperature();

  //print temperature
  Serial.print("temperature: ");
  Serial.print(c);
  Serial.println("* C");

//  rtc.adjust(DateTime(2020, 7, 27, 11, 19, 30));   // would set to February 28, 2015 at 14:50:00 (2:50pm)

}


void loop () {
 
    
    //get time 
    tt = rtc.now(); // read the time from the DS3231 RTC chip
    
    Serial.print(tt.year(), DEC);
    Serial.print('/');
    Serial.print(tt.month(), DEC);
    Serial.print('/');
    Serial.print(tt.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[tt.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(tt.hour(), DEC);
    Serial.print(':');
    Serial.print(tt.minute(), DEC);
    Serial.print(':');
    Serial.print(tt.second(), DEC);
    Serial.println();
    
    Serial.println();
    
}
