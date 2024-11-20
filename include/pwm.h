#ifndef PWM_H
#define PWM_H

#include <Arduino.h>

class pwm_tim_1
{
private:
    int pin;
public:
    void set_dc(int duty_cycle);
    pwm_tim_1(int pin);
    void innit();
};


pwm_tim_1::pwm_tim_1(int _pin)
{
    pin = _pin;
}

void pwm_tim_1::set_dc(int duty_cycle){
    OCR3A = duty_cycle;
}

void pwm_tim_1::innit(){

    pinMode(pin, OUTPUT);
  TCCR3A = _BV(COM3A1) | _BV(WGM31);
  TCCR3B = _BV(WGM33) | _BV(WGM32) | _BV(CS30);
  ICR3 = 799;
  OCR3A = 0;
}

#endif
