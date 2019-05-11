#include "config.h"

ThingerESP8266 thing(THINGER_USERNAME, THINGER_DEVICE_ID, THINGER_DEVICE_CREDENTIAL);

MyScreen myScreen = MyScreen();
MyFan myFan = MyFan();              //Fan management
MyNtpTime myNtpTime = MyNtpTime();  //Clock management
MyThermostat thermostat = MyThermostat();


void setup()
{
  Serial.begin(115200);
  Serial.println("Starting temperature controlled fan.");

  pinMode(BUTTON_PLUS, INPUT);
  pinMode(BUTTON_MINUS, INPUT);
  pinMode(FAN_PIN, OUTPUT);


  bool bConnected = connectToWifi();

  myFan.begin();
  thermostat.begin(DHT_PIN);
  myScreen.begin(OLED_SDA_PIN, OLED_SCL_PIN);

  myNtpTime.begin();

  desiredTemp = 30;

  // Value to be sent when "handle" function is invoked
  thing["Temp"] >> outputValue(currentTemp);
  thing["Fan_speed"] >> outputValue(myFan.getSpeed());
}

//-------------------------------------------------------------------------------------------
void loop()
{
  bool updateScreenInfo = false;

  unsigned long currentMillis = millis();
  //Even though every 49 days millis() overflows, this will work. We're substracting UNSIGNED longs
  //https://www.norwegiancreations.com/2018/10/arduino-tutorial-avoiding-the-overflow-issue-when-using-millis-and-micros/

  //Using millis y much efficient than delay
  
  //--------------------------------------------------------------
  if ((unsigned long)(currentMillis - lastMillisButtonCheck) > BUTTON_CHECK_PERIOD)
  {
    lastMillisButtonCheck = currentMillis;
    //Sólo actualizo la pantalla si se toca un botón para que el usuario vea los cambios al momento.
    updateScreenInfo = readButtons(); 
  }
  //--------------------------------------------------------------
  if ((unsigned long)(currentMillis - lastMillisTempRead) > TEMP_READ_PERIOD)
  {
    lastMillisTempRead = currentMillis;
    
    float t = thermostat.getTemp();
    Serial.println("Temp read: " + String(t));
    //en caso de una lectura erronea, se mantiene la última lectura válida
    if (!isnan(t))
    {
      currentTemp = t;
    }
    myFan.setTemperatures(currentTemp, desiredTemp);
  }
  //--------------------------------------------------------------
  if ((unsigned long)(currentMillis - lastMillisClockUpdate) > CLOCK_UPDATE_PERIOD)
  {
    lastMillisClockUpdate = currentMillis;
    Serial.println("Clockupdate");
    updateScreenInfo = true;
    thing.handle();
  }
  //--------------------------------------------------------------
  if ((unsigned long)(currentMillis - lastMillisClockSync) > CLOCK_SYNC_PERIOD)
  {
    lastMillisClockSync = currentMillis;
    Serial.println("Clock Sync");
    myNtpTime.syncTime();
  }
  //--------------------------------------------------------------
  if((unsigned long)(currentMillis - lastMillisWifiCheck) > WIFI_CHECK_PERIOD)
  {
    lastMillisWifiCheck = currentMillis;
    Serial.println("WifiCheck");
    if (WiFi.status() != WL_CONNECTED)
    {
      connectToWifi();
    }
  }
  //--------------------------------------------------------------
  if (updateScreenInfo)
  {
    myScreen.DrawScreenInfo(myFan.getSpeed(), currentTemp, desiredTemp, myNtpTime.getTime());
  }
  
}



bool readButtons()
{
  bool updateScreenInfo = true;
  button_plus_state   = digitalRead(BUTTON_PLUS);
  button_minus_state  = digitalRead(BUTTON_MINUS);

  if (button_plus_state == HIGH)
  {
    desiredTemp += 1;
    Serial.println("Temperatura deseada: " + String(desiredTemp));
    myFan.setTemperatures(currentTemp, desiredTemp);
  }
  if (button_minus_state == HIGH)
  {
    desiredTemp -= 1;
    Serial.println("Temperatura deseada: " + String(desiredTemp));
    myFan.setTemperatures(currentTemp, desiredTemp);
  }
  else
  {
    //No changes
    updateScreenInfo = false;
  }

  return updateScreenInfo;
}




bool connectToWifi()
{
  bool bConnected = false;
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  WiFi.begin(SSID, SSID_PASSWORD);

  int trials = 0;
  while (WiFi.status() != WL_CONNECTED && trials < 100)
  {
    Serial.print(".");
    delay(100);
    trials ++;
  }
  
  if (WiFi.status() == WL_CONNECTED)
  {
    bConnected = true;
    Serial.println("Conectado al wifi " + String(SSID));
  }
  else
  {
    Serial.println("Agotados los intentos de conectar a " + String(SSID));
  }
  return bConnected;
}
