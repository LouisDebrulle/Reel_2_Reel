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


    state_machine();
    bool step();
    void change_state(Board& _board);
};


state_machine::state_machine() 
{
  state = off;
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
        _board.init();
    } else {
        state = on;
        digitalWrite(13, HIGH);
    }
}

#endif




