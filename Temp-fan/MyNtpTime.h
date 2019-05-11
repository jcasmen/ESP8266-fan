#ifndef MyNtpTime_h
#define MyNtpTime_h

#include <Arduino.h>



class MyNtpTime
{
  public:
    MyNtpTime();


    void begin();
    String getTime();
    void syncTime();

  private:
    //int current_fan_speed;

    int hour;
    int minute;
    int second;
  

};
#endif
