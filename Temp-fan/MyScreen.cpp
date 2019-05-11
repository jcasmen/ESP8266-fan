
#include "MyScreen.h"
#include <Arduino.h>

MyScreen::MyScreen()
{

}


void MyScreen::begin(int sda, int scl)
{
  display = new OLED(sda, scl);
  display->begin();

}

void MyScreen::DrawScreenInfo(int fanSpeed, float currentTemp, int desiredTemp, String currentTime)
{
  display->clear();

  //speed bar (uses 104 out of 128px width)
  float bar_width = (float)(fanSpeed) / 100 /*MAX_FAN_SPEED*/ * 104;
  display->draw_rectangle(0, 2, bar_width, 4, OLED::SOLID);

  this->DrawText(104, 0, String(fanSpeed) + "%");
  //mensaje temperatura actual
  String msg2 = "Curr: " + String(currentTemp) + " C";
  this->DrawText(2, 8, msg2);

  //mensaje temperatura
  String msg3 = "Desi: " + String(desiredTemp) + " C";
  this->DrawText(2, 16, msg3);

  this->DrawText(60, 24, currentTime);

  //mostramos todo lo enviado al buffer de la pantalla
  display->display();

}

void MyScreen::DrawText(uint x, uint y, String text)
{
  int str_len = text.length() + 1;
  char char_array[str_len];

  text.toCharArray(char_array, str_len);
  display->draw_string(x, y, char_array);

}
