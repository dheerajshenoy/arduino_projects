#include <Wire.h>
#include <ds3231.h>
 
struct ts t; 
int hr, mi, se, da, mo, ye, day, mon, year, hour, minute, sec;

void getAlarmTime() {
  hr = 11;
  mi = 25;
  se = 0;
  da = 9;
  mo = 1;
  ye = 2021; 
}

void checkAlarm(int dd, int mm, int yy, int hh, int m, int sec) {
   if(dd == da && mm == mo && yy == ye && hh == hr && m == mi && sec == se)
      {
        Serial.print("ALARM!");
        
      }
      
   else
      Serial.print("NOT YET");
}

void setup() {
  getAlarmTime();
  Serial.begin(9600);
  Wire.begin();
  DS3231_init(DS3231_CONTROL_INTCN);
  /*----------------------------------------------------------------------------
  In order to synchronise your clock module, insert timetable values below !
  ----------------------------------------------------------------------------*/
  t.hour=11; 
  t.min=29;
  t.sec=30;
  t.mday=9;
  t.mon=1;
  t.year=2021;
 
  DS3231_set(t); 
}

void loop() {
  DS3231_get(&t);
  
  Serial.print("Date : ");
  Serial.print(t.mday);
  Serial.print("/");
  Serial.print(t.mon);
  Serial.print("/");
  Serial.print(t.year);
  Serial.print("\t Hour : ");
  Serial.print(t.hour);
  Serial.print(":");
  Serial.print(t.min);
  Serial.print(".");
  Serial.println(t.sec);
  
  day = t.mday;
  mon = t.mon;
  year = t.year;
  hour = t.hour;
  minute = t.min;
  sec = t.sec;
  
  checkAlarm(day, mon, year, hour, minute, sec);
  delay(1000);

}
