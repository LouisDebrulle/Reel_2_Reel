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
    double analog_sense = analogRead(pin2);
    double voltage = analog_sense * 5.0 / 1023.0;
    if (voltage < 0.5){pos = 0;}
    else if (voltage >4.5){pos = 25;}
    else{pos = (voltage - 0.5) * 25.0 / (4.5 - 0.5);}
    return pos;
}

void pos_sensor::innit(){
    pinMode(pin1,INPUT);
    pinMode(pin2,INPUT);
}


#endif
