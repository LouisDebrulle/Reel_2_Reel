#include <Arduino.h>
#include <arduino-timer.h>

class Encoder
{
private:
public:
    const int A_pin;  
    const int B_pin;

    const int pulses_per_rev = 2048; 
    unsigned long last_pulse_time = 0;
    unsigned long pulse_interval = 0;
    int direction = 1;
    double speed();
    
    Encoder(int A_pin, int B_pin);
    
    void step();
    double get_speed();
};

void Encoder::step() {
    unsigned long current_time = micros();
    pulse_interval = current_time - last_pulse_time;
    last_pulse_time = current_time;

    if (digitalRead(B_pin) == HIGH) {
        direction = 1;  
    } else {
        direction = -1;
    }
}

Encoder::Encoder(int A_pin, int B_pin) 
    : A_pin(A_pin), B_pin(B_pin)
{
    pinMode(A_pin, INPUT);
    pinMode(B_pin, INPUT);
}



double Encoder::get_speed(){
    double speed = (60.0 * 1e6) / (double(pulses_per_rev) * pulse_interval);
    return speed *= direction;
}




