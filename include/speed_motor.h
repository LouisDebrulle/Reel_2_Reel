#ifndef Speed_motor_H
#define Speed_motor_H

#include <Arduino.h>
#include "motor.h"

class Speed_motor : public Motor
{
public:
void init();
    Speed_motor(Board& board, int max_value);
};





Speed_motor::Speed_motor(Board& board, int max_value) : Motor(board, max_value)
{
    feedback_pin = _board.motor1.feedback_pin;
    control_pin = _board.motor1.control_pin;
    dir_pin = _board.motor1.dir_pin;
    enable_pin = _board.motor1.energize_pin;

}

void Speed_motor:: init(){
    digitalWrite(enable_pin, HIGH);
    digitalWrite(dir_pin, HIGH);
}






#endif
