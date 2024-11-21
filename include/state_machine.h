#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <Arduino.h>
#include "board.h"
#include "motor.h"

class state_machine
{
private:
public:
    enum status{
        on,
        off
    };
    status state;

    unsigned long last_time;
    state_machine();
    bool step();
    void change_state(Board& _board);
    double get_time();
};


state_machine::state_machine() 
{
  state = off;
  last_time = 0;
}

bool state_machine::step(){
    if (state == on) {
        return true;
    } return false;
}

void state_machine::change_state(Board& _board) {
    if (state == on) {
        state = off;
        digitalWrite(13, LOW);
        digitalWrite(_board.motor1.enable_pin, HIGH);
        digitalWrite(_board.motor2.enable_pin, HIGH);
        _board.init();
    } else {
        last_time = millis();
        state = on;
        digitalWrite(13, HIGH);
        
    }
}

double state_machine::get_time(){
    double current_time = millis();
    return current_time - last_time;
}

#endif




