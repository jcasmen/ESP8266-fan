
#ifndef MyFan_h
#define MyFan_h


#define FAN_PIN       13 //D7

#define  MAX_DIFF_DEGREE    5
#define  MIN_FAN_SPEED    0
#define  MAX_FAN_SPEED    100

enum modo_ventilador
{
  automatic,
  manual
};

class MyFan
{
  public:
    MyFan();

    void begin();

    int getSpeed();
    void setTemperatures(float current, int desired);

  private:
    int current_fan_speed;
    int desired_temp;
    float current_temp;
    unsigned long last_stop; //ultimo valor de millis() en que la velocidad fue cero

    void calculateSpeed();

};
#endif
