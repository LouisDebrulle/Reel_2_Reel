#ifndef PWM_H
#define PWM_H

#include <Arduino.h>

class pwm_tim_1
{
private:
    int pin1, pin2;
public:
    void set_dc(int value, int pin);
    pwm_tim_1(int _pin1, int _pin2);
    void innit();
};


pwm_tim_1::pwm_tim_1(int _pin1, int _pin2)
{
    pin1 = _pin1; 
    pin2 = _pin2; 

}

void pwm_tim_1::set_dc(int value, int pin) {
    if (pin == pin1) {OCR4A = value;}
    else if (pin == pin2){OCR4B = value;}
    else {return;}
    
}

void pwm_tim_1::innit() {
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    TCCR4A = _BV(COM4A1) | _BV(COM4B1) | _BV(WGM41);
    TCCR4B = _BV(WGM43) | _BV(WGM42) | _BV(CS40);
    ICR4 = 10000;
    OCR4A = 0;
    OCR4B = 0;
}


#endif
