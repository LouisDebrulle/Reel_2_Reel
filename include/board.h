#ifndef BOARD_H
#define BOARD_H

#include "Encoder.h" 
#include "pwm.h"
#include "pin.h"




class Board {

public:

    Encoder _encoder = Encoder(encoderPinA, encoderPinB);
    pwm_tim_1 _pwm = pwm_tim_1(motor1_speed_pin, motor2_speed_pin);

    

    struct
    {
        int speed_pin;
        int out_pin;
        int break_pin;
        int energize_pin;
    }motor1 = {.speed_pin = motor1_speed_pin, 
                .out_pin = motor1_out_pin,
                .break_pin = motor1_break_pin,
                .energize_pin = motor1_energize_pin},
    motor2 = {.speed_pin = motor2_speed_pin, 
                .out_pin = motor2_out_pin,
                .break_pin = motor2_break_pin,
                .energize_pin = motor2_energize_pin};
    
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
