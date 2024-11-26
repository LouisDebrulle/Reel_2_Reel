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
        running,
        stopped,
        on,
        off,
    };
    status state;
    Board& _board;

    unsigned long last_time;
    state_machine(Board& board);
    bool step();
    void change_state();
    double get_time();
};


state_machine::state_machine(Board& board):_board(board)
{
  state = off;
  last_time = 0;
}

bool state_machine::step(){
    if (state == on) {
        return true;
    } return false;
}

void state_machine::change_state() {
    if (state == on) {
        state = off;
        digitalWrite(13, LOW);
        digitalWrite(_board.motor1.break_pin, HIGH);
        digitalWrite(_board.motor2.break_pin, HIGH);
        _board.init();
    } else {
        last_time = millis();
        state = on;
        digitalWrite(13, HIGH);
        digitalWrite(_board.motor1.break_pin, LOW);
        digitalWrite(_board.motor2.break_pin, LOW);

        
    }
}

double state_machine::get_time(){
    double current_time = millis();
    return current_time - last_time;
}

#endif




