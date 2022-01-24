#include <RTClib.h>
RTC_DS1307 rtc;

unsigned long unixTime_Start;
unsigned long unixTime_Current;

void rtcSetup(){
  int cnt = 0;
  while ((!rtc.begin()) && (cnt < 5)) {
    Serial.println("RTC failed, or not present");
    delay(1000);
    cnt++;
  }
  if (!rtc.isrunning()) {
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void getCurrentTime(){
  DateTime now = rtc.now();
  int hh = now.hour();
  int mm = now.minute();
  int sec = now.second();
  showTimeGen(hh, mm);
}
unsigned long getCurrentUnixTime() {
    DateTime now = rtc.now();
    return now.unixtime();
}

// this function woll mark the start of measure
// and save the time in general variable
void setMeasureStart(){
  unixTime_Start = getCurrentUnixTime();
}

int getSecPassed(){
  unixTime_Current = getCurrentUnixTime();
  int ret = unixTime_Current - unixTime_Start;
  return ret;
}
