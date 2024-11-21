#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include "board.h"

class Motor
{
private:
    
public:
    Board& _board;

    void set_speed(double speed);
    void enable_motor(bool motor_state);
    Motor(Board& board);
    
};


Motor::Motor(Board& board):_board(board)
{
    
}


void Motor::enable_motor(bool motor_state){
    digitalWrite(_board.motor1.enable_pin, HIGH);
}

void Motor::set_speed(double speed){
    _board._pwm.set_dc(300, 700);
}




#endif
