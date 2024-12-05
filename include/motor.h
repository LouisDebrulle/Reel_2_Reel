#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include "board.h"

class Motor
{
private:
    const int MAX_SPEED = 30;
    
public:
    Board& _board;

    void init();
    void set_speed(double speed1, double speed2);
    int get_dc(double speed);
    void enable_motor(bool motor_state);
    Motor(Board& board);
    
};

void Motor::init(){
    pinMode(_board.motor1.energize_pin, OUTPUT);
    digitalWrite(_board.motor1.energize_pin, HIGH);
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

int Motor::get_dc(double speed){
    return int(ICR4/MAX_SPEED *speed);
}




#endif
