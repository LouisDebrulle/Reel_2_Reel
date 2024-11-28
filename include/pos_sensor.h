#ifndef POS_SENSOR_H
#define POS_SENSOR_H

#include <Arduino.h>

class pos_sensor
{
private:
    int pin1, pin2;
    double pos;
public:
    
    pos_sensor(int _pin1, int _pin2);
    void innit();
    double get_pos();
};


pos_sensor::pos_sensor(int _pin1, int _pin2)
{
    pos = 0;
    pin1 = _pin1; 
    pin2 = _pin2; 
}

double pos_sensor::get_pos(){
    double pos_sens = analogRead(pin1);
    pos = (pos_sens * 25.0 / 1023.0) - 12.5;
    return pos;
}

void pos_sensor::innit(){
    pinMode(pin1,INPUT);
    pinMode(pin2,INPUT);
}


#endif
