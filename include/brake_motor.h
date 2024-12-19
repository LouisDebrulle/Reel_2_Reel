#ifndef BRAKE_MOTOR_H
#define BRAKE_MOTOR_H

#include <Arduino.h>
#include "motor.h"

class Breake_motor : public Motor
{
    public:
    Breake_motor(Board& board, int max_value);
};



Breake_motor::Breake_motor(Board& board, int max_value) : Motor(board, max_value)
{
    feedback_pin = _board.motor2.feedback_pin;
    control_pin = _board.motor2.control_pin;
    dir_pin = _board.motor2.dir_pin;
    enable_pin = _board.motor2.energize_pin;
}



#endif
