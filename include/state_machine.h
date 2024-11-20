#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <Arduino.h>
#include "board.h"

class state_machine
{
private:
public:
    enum status{
        on,
        off
    };
    status state;
    Board& _board;
    state_machine(Board& board);
    void step();
    void change_state();
};


state_machine::state_machine(Board& board) 
    :_board(board)
{
  state = off;
}

void state_machine::step(){
    if (state == on) {
        
    } else if (state == off) {
        
    }
}

void state_machine::change_state() {
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




