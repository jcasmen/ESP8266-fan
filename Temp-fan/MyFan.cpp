
#include "MyFan.h"
#include <Arduino.h>

#define MAX_PWM_VALUE 1023 //en el ESP8266 la modulación es de 10 bits (0-1023) no de 8 (0-255) como arduino
#define MIN_PWM_VALUE 128

#define LONG_STOP 1000 //Tiempo en que consideramos que el ventilador se ha podido detener completamente

MyFan::MyFan()
{

}


void MyFan::begin()
{
  setTemperatures(25, 25);
  analogWriteFreq(20000); //Hz
}


void MyFan::setTemperatures(float current, int desired)
{
  current_temp = current;
  desired_temp = desired;

  calculateSpeed();

}

void MyFan::calculateSpeed()
{
  float difference = current_temp - desired_temp;
  //la velocidad es proporcional a la diferencia entre la temperatura actual y la deseada. A partir de 5 grados, velocidad al 100%
  int new_speed = difference > 0 ? (int)((min(difference, (float)MAX_DIFF_DEGREE)) / MAX_DIFF_DEGREE * 100) : 0;
  //Serial.println("Curr: " + String(current_temp) + " Des: " + String(desired_temp) + " V: " + String(s) + "%");

  if (current_fan_speed >  0 && new_speed == 0)
  {
    //parada del ventilador
    last_stop = millis();
    Serial.println("PARADA ventilador");
  }
  if (current_fan_speed == 0 && new_speed > 0)
  {
    //rearranque
    if (millis() - last_stop > LONG_STOP)
    {
      //Si el ventilador lleva un tiempo parado, hay que vencer la inercia inicial para que se ponga en
      //marcha. Con un PWM muy bajo, a veces no se consigue arrancar. Por eso, le damos una "patada" con valor
      //máximo durante un momento, para que coja revoluciones y luego se mantenga en marcha con la nueva velocidad.
      Serial.println("ARRANQUE ventilador con patada");
      analogWrite(FAN_PIN,  MAX_PWM_VALUE);
      delay(1000);

    }
    else
    {
      Serial.println("ARRANQUE ventilador");
    }
  }

  current_fan_speed = new_speed;


  int pinLevel = 0;
  if (current_fan_speed > 0)
  {
    //No hacemos un mapeo directo, porque el ventilador en valores muy bajos de salida, no se mantiene en movimiento.
    //Establezco un nivel mínimo "a ojo" que haga que el ventilador gire a bajas rpm.
    pinLevel = map(new_speed, 0, 100, MIN_PWM_VALUE, MAX_PWM_VALUE);
  }

  analogWrite(FAN_PIN, pinLevel);
}

int MyFan::getSpeed()
{
  return current_fan_speed;
}
