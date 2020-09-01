#include <DS1302Module.h>

DS1302Module ds1302Module = DS1302Module(9, 8, 10);// DAT(IO), CLK(SCLK), RST(CE)

void setup() {
  Serial.begin(9600);
  ds1302Module.initial();
  ds1302Module.setYear(20);
  ds1302Module.setMonth(12);
  ds1302Module.setDay(31);
  ds1302Module.setWeekday(8);
  ds1302Module.setHours(23);
  ds1302Module.setMinutes(59);
  ds1302Module.setSeconds(55);
}

void loop() {
  delay(1000);
  Serial.println(DS1302Module::toMonthLongName(ds1302Module.getMonth()));
  Serial.println(DS1302Module::toMonthShortName(ds1302Module.getMonth()));
  Serial.println(DS1302Module::toWeekdayLongName(ds1302Module.getWeekday()));
  Serial.println(DS1302Module::toWeekdayShortName(ds1302Module.getWeekday()));
  Serial.println(DS1302Module::toISO8601DateTime(ds1302Module.getYear(), ds1302Module.getMonth(), ds1302Module.getDay(), ds1302Module.getHours(), ds1302Module.getMinutes(), ds1302Module.getSeconds()));
}
