

#include "MyFan.h"
#include "MyNtpTime.h"
#include "MyThermostat.h"
#include "MyScreen.h"


#include <ESP8266WiFi.h>
#include <ThingerESP8266.h>


#define OLED_SDA_PIN 14
#define OLED_SCL_PIN 12


#define BUTTON_PLUS   5  //(D1)
#define BUTTON_MINUS  2  //(D4)

#define DHT_PIN D2 // what digital pin we're connected to

#define THINGER_USERNAME "YOUR THINGER USERNAME"
#define THINGER_DEVICE_ID "YOUR THINGER DEVICE ID"
#define THINGER_DEVICE_CREDENTIAL "YOUR THINGER DEVICE CREDENTIAL"  //generado en el panel de control del dispositivo

#define SSID          "YOUR WIFI'S SSID"
#define SSID_PASSWORD "YOUR WIFI'S PASSWORD"

//Periodos en milisegundos
#define BUTTON_CHECK_PERIOD   100
#define CLOCK_UPDATE_PERIOD  1000
#define CLOCK_SYNC_PERIOD     60*60*1000  //60 MIN
#define TEMP_READ_PERIOD      1000
#define WIFI_CHECK_PERIOD     60*1000     //1 MIN


int button_plus_state   = LOW;
int button_minus_state  = LOW;

int desiredTemp = 0;
float currentTemp = 0;

unsigned long lastMillisButtonCheck = 0;
unsigned long lastMillisClockUpdate = 0;
unsigned long lastMillisClockSync = 0;
unsigned long lastMillisTempRead = 0;
unsigned long lastMillisWifiCheck = 0;



//Referencias:
// http://bildr.org/2011/03/high-power-control-with-arduino-and-tip120/
