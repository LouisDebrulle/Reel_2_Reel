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

    pinMode(control_pin, OUTPUT);
    pinMode(feedback_pin, INPUT);
    pinMode(dir_pin, OUTPUT);
    pinMode(enable_pin, OUTPUT);

}

void Speed_motor:: init(){
    digitalWrite(enable_pin, HIGH);
    direction = false;
    digitalWrite(dir_pin, direction);
}






#endif
