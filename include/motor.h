#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include "board.h"

class Motor
{
private:
    const int MAX_SPEED = 500;
    int last_time;
    int pulse_intervall;
public:
    Board& _board;

    void init();
    void set_speed(double speed1, double speed2);
    int get_dc(double speed);
    void enable_motor(bool motor_state);
    void measure_feedback();
    double get_speed_feedback();
    Motor(Board& board);
    
};

void Motor::init(){
    pinMode(_board.motor1.energize_pin, OUTPUT);
    pinMode(21, INPUT);
    digitalWrite(_board.motor1.energize_pin, HIGH);
}

void Motor::measure_feedback(){
    int current_time = millis();
    pulse_intervall = current_time - last_time;
    last_time = current_time;
}

double Motor::get_speed_feedback(){
    return double(pulse_intervall)/2.083 *MAX_SPEED;
}

Motor::Motor(Board& board):_board(board)
{
    last_time = 0;
    pulse_intervall = 0;
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
