#ifndef BRAKE_MOTOR_H
#define BRAKE_MOTOR_H

#include <Arduino.h>
#include "motor.h"
#include "linear_curve.h"

class Breake_motor : public Motor
{
    public:
    Breake_motor(Board& board, int max_value);
    void init();
};




Breake_motor::Breake_motor(Board& board, int max_value) : Motor(board, max_value)
{
    feedback_pin = _board.motor2.feedback_pin;
    control_pin = _board.motor2.control_pin;
    dir_pin = _board.motor2.dir_pin;
    enable_pin = _board.motor2.energize_pin;

    pinMode(control_pin, OUTPUT);
    pinMode(feedback_pin, INPUT);
    pinMode(dir_pin, OUTPUT);
    pinMode(enable_pin, OUTPUT);
}

void Breake_motor:: init(){
    digitalWrite(enable_pin, HIGH);
    direction = true;
    digitalWrite(dir_pin, direction);
}


#endif
