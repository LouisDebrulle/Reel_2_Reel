#include <Arduino.h>

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
    void step();
    void change_state();
};


state_machine::state_machine()
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
    } else {
        state = on;
        digitalWrite(13, HIGH);
    }
}



