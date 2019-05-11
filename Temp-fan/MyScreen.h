#ifndef MyScreen_h
#define MyScreen_h

#include <Arduino.h>
#include <oled.h>

class MyScreen
{
  public:
    MyScreen();


    void begin(int sda, int scl);

    void DrawScreenInfo(int fanSpeed, float currentTemp, int desiredTemp, String currentTime);

  private:

    OLED* display;

    void DrawText(uint x, uint y, String text);

};
#endif
