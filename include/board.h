#ifndef BOARD_H
#define BOARD_H

#include "Encoder.h" 
#include "pwm.h"




class Board {

public:

    Encoder _encoder;
    pwm_tim_1 _pwm;
    Board(int encoderPinA, int encoderPinB, int pwmPin)
        : _encoder(encoderPinA, encoderPinB), _pwm(pwmPin) {}

    void init() {
        _pwm.innit();
        _encoder.innit();
        pinMode(13, OUTPUT); 
    }

    void blink(){
        digitalWrite(13,HIGH);
    }

   
};

#endif
