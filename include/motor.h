#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include "board.h"

class Motor
{
private:
    
public:
    Board& _board;

    void init();
    void set_speed(double speed1, double speed2);
    void enable_motor(bool motor_state);
    Motor(Board& board);
    
};

void Motor::init(){
    pinMode(_board.motor1.energize_pin, OUTPUT);
    pinMode(_board.motor1.break_pin, OUTPUT);
    digitalWrite(_board.motor1.energize_pin, HIGH);
    digitalWrite(_board.motor1.break_pin, HIGH);
}

Motor::Motor(Board& board):_board(board)
{
    
}


void Motor::enable_motor(bool motor_state){
    digitalWrite(_board.motor1.break_pin, HIGH);
}

void Motor::set_speed(double speed1, double speed2){
    _board._pwm.set_dc(speed1, speed2);
}




#endif
