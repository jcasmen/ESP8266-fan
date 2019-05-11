
#include "MyNtpTime.h"
#include <time.h>
#include <Arduino.h>

MyNtpTime::MyNtpTime()
{

}


void MyNtpTime::begin()
{
  syncTime();
}

String MyNtpTime::getTime()
{
  time_t now = time(nullptr);

  struct tm* timeinfo;
  timeinfo = localtime(&now);

  hour = timeinfo->tm_hour;
  minute = timeinfo->tm_min;
  second = timeinfo->tm_sec;

  char buffer [16];
  sprintf (buffer, "%02u:%02u:%02u", hour, minute, second);

  String strTime = String(buffer);
  return strTime;
}


void MyNtpTime::syncTime()
{
  configTime(2 * 3600/*timezone_offset_secs*/, /*dst_offset_secs*/0, "pool.ntp.org", "time.nist.gov");

  Serial.println("\nWaiting for time");
  while (!time(nullptr)) {
    Serial.print(".");
    delay(100);
  }
  Serial.println("");
}
