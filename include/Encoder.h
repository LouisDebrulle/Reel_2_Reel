#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>
#include "buffer.h"




class Encoder
{
private:
public:
    const int A_pin;  
    const int B_pin;

    const int pulses_per_rev = 2048; 
    buffer _buffer;
    unsigned long last_pulse_time;
    long pulse_interval;
    
    
    Encoder(int A_pin, int B_pin);
    
    void step();
    double get_speed();
    void innit();
    int get_puls_count();
    int get_puls_sum();
    int get_pulse_interval();
};

void Encoder::step() {
    unsigned long current_time = millis();
    pulse_interval = current_time - last_pulse_time;
    
    last_pulse_time = current_time;

    
    if (digitalRead(B_pin) == HIGH) {
        _buffer.add(pulse_interval);  
    } else {
        _buffer.add(-pulse_interval);
    }
}

Encoder::Encoder(int A_pin, int B_pin) 
    : A_pin(A_pin), B_pin(B_pin)
{
    _buffer = buffer();
    pinMode(A_pin, INPUT);
    pinMode(B_pin, INPUT);
}



double Encoder::get_speed(){
    double average_time = _buffer.get_average();
    double speed = (60.0 * 1e3) / (double(pulses_per_rev) * average_time);
    _buffer.clear();
    return speed;
}

int Encoder::get_puls_count(){
    return _buffer.get_count();
}

int Encoder::get_puls_sum(){
    return _buffer.get_sum();
}

int Encoder::get_pulse_interval(){
    return pulse_interval;
}

void Encoder::innit(){
    last_pulse_time = 0;
    _buffer.clear();
}


#endif

