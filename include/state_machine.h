#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <Arduino.h>
#include "board.h"
#include "motor.h"

enum status{
        off,
        on,
        running,
    };


class state_machine
{
private:
public:
    
    status state;
    Board& _board;

    unsigned long last_time;
    state_machine(Board& board);
    void change_state();
    double get_time();
};


state_machine::state_machine(Board& board):_board(board)
{
  state = off;
  last_time = 0;
}


void state_machine::change_state() {
    switch (state)
    {
    case off:
        if (digitalRead(on_off_pin)) {
            state = on; 
            Serial.println("on");
            last_time = millis(); 
            return;}
        break;

    case on:
        if(!digitalRead(on_off_pin)){
            state = off; 
            Serial.println("off");
            last_time = millis();  
            return;}
        if (digitalRead(start_motor_pin)) {
            state = running; 
            Serial.println("running"); 
            last_time = millis(); 
            return;}
        break;
    case running:
        if (!digitalRead(on_off_pin)) {state = off;
            Serial.println("off"); 
            last_time = millis(); 
            return;}
        if (!digitalRead(start_motor_pin)) {state = on;
            Serial.println("on");
            last_time = millis(); 
            return;}
        break;
        
   
    }
       
        
}

double state_machine::get_time(){
    double current_time = millis();
    return current_time - last_time;
}

#endif




