#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include "board.h"

class Motor
{   
public:
    int MAX_VALUE;
    int last_time;
    int pulse_intervall;
    bool direction;

    int feedback_pin; int control_pin; int dir_pin; int enable_pin;
    Board& _board;

    void set(double value);
    void enable();
    void change_direction();

    int get_dc(double value);
    void measure_feedback();
    double get_feedback();
    Motor(Board& board, int _max_value);
    
};


Motor::Motor(Board& board, int _max_value) :_board(board), MAX_VALUE(_max_value)
{
    last_time = 0;
    pulse_intervall = 0;
}

void Motor::set(double value){
    _board._pwm.set_dc(value, control_pin);
}


void Motor::change_direction(){
    Serial.println("change dir");
    direction = !direction;
    digitalWrite(dir_pin, direction);
}

void Motor::enable(){
    digitalWrite(enable_pin, LOW);
}



void Motor::measure_feedback(){
    int current_time = millis();
    pulse_intervall = current_time - last_time;
    last_time = current_time;
}

double Motor::get_feedback(){
    return double(pulse_intervall)/2.083 *MAX_VALUE;
}


int Motor::get_dc(double value){
    return int(ICR4/MAX_VALUE *value);
}




#endif
