
#include "MyThermostat.h"

#include <Arduino.h>

MyThermostat::MyThermostat()
{

}


void MyThermostat::begin(int dht_pin)
{
  //NO USAR LA FUNCIÓN BEGIN en esta librería para ESP
  //dht.begin();
  dht.setup(dht_pin, DHTesp::DHT22);
}


float  MyThermostat::getTemp()
{
  float t = 0;
  //delay(dht.getMinimumSamplingPeriod());

  // Read temperature as Celsius (the default)
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  t = dht.getTemperature();
  if (isnan(t))
  {
    Serial.println("Error al leer temperatura: " + String(dht.getStatusString()));
  }
  return t;
}


float  MyThermostat::getHumidity()
{
  float h = 0;
  // Read temperature as Celsius (the default)
  h = dht.getHumidity();

  return h;
}
