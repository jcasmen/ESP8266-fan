#ifndef MyThermostat_h
#define MyThermostat_h

#include <DHTesp.h>

#define DHTTYPE DHT22 // DHT 22 (AM2302), AM2321



// Important to note that when wired to the esp8266mod
// even though pin "4" is specified data is on D2 of the 8266.


// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor




class MyThermostat
{
  public:
    MyThermostat();


    void begin(int dth_pin);
    float getTemp();
    float getHumidity();


  private:
    DHTesp dht;
};
#endif
