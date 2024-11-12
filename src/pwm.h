#include <Arduino.h>

class pwm_tim_1
{
private:
public:
    void set_dc(int duty_cycle);
    pwm_tim_1(int pin);
};


pwm_tim_1::pwm_tim_1(int pin)
{
 pinMode(pin, OUTPUT);

  TCCR3A = _BV(COM3A1) | _BV(WGM31);
  TCCR3B = _BV(WGM33) | _BV(WGM32) | _BV(CS30);
  ICR3 = 799;
  OCR3A = 350;   
}

void pwm_tim_1::set_dc(int duty_cycle){
    OCR3A = duty_cycle;
}