#include <Wire.h>
#include <ds3231.h>


struct ts t; 
int hr, mi, se, da, mo, ye, day, mon, year, hour, minute, sec;
bool alarm=false;

int stopBtn = 6;

// Alarm Function

void getAlarmTime() {
  hr = 1;
  mi = 15;
  se = 0;
  da = 9;
  mo = 1;
  ye = 2021; 
}

// Check if the time is the same as the alarm time

void checkAlarm(int dd, int mm, int yy, int hh, int m, int sec) {
   if(dd == da && mm == mo && yy == ye && hh == hr && m == mi && sec == se)
      {
        alarm = true;
        while(alarm == true)
          {
            Serial.print("ALARM!");
            delay(5000);
          }
      }
}

void setup() {
  pinMode(stopBtn, INPUT);
  getAlarmTime();
  Serial.begin(9600);
  Wire.begin();
  DS3231_init(DS3231_CONTROL_INTCN);
  /*----------------------------------------------------------------------------
  In order to synchronise your clock module, insert timetable values below !
  ----------------------------------------------------------------------------*/
  
  t.hour=1; 
  t.min=20;
  t.sec=20;
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

  digitalRead(stopBtn);
  if (stopBtn == HIGH) {
      alarm = false;
      Serial.print("BB");
  }
      
  
  day = t.mday;
  mon = t.mon;
  year = t.year;
  hour = t.hour;
  minute = t.min;
  sec = t.sec;
  
  checkAlarm(day, mon, year, hour, minute, sec);
  delay(1000);

}
