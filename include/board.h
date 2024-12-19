#ifndef BOARD_H
#define BOARD_H

#include "Encoder.h" 
#include "pwm.h"
#include "pin.h"
#include "pos_sensor.h"




class Board {

public:

    Encoder _encoder = Encoder(encoderPinA, encoderPinB);
    pwm_tim_1 _pwm = pwm_tim_1(motor1_control_pin, motor2_control_pin);
    pos_sensor _pos_sensor = pos_sensor(sensor_pos_pin, sensor_neg_pin);


    

    struct
    {
        int control_pin;
        int feedback_pin;
        int dir_pin;
        int energize_pin;
    }motor1 = {.control_pin = motor1_control_pin, 
                .feedback_pin = motor1_out_pin,
                .dir_pin = motor1_dir_pin,
                .energize_pin = motor1_energize_pin},
    motor2 = {.control_pin = motor2_control_pin, 
                .feedback_pin = motor2_out_pin,
                .dir_pin = motor2_dir_pin,
                .energize_pin = motor2_energize_pin};
    
    void init() {

        pinMode(motor1.control_pin, OUTPUT);
        pinMode(motor1.feedback_pin, INPUT);
        pinMode(motor1.dir_pin, OUTPUT);
        pinMode(motor1.energize_pin, OUTPUT);

        pinMode(motor2.control_pin, OUTPUT);
        pinMode(motor2.feedback_pin, INPUT);
        pinMode(motor2.dir_pin, OUTPUT);
        pinMode(motor2.energize_pin, OUTPUT);

        _pwm.innit();
        _encoder.innit();
        _pos_sensor.innit();
        pinMode(13, OUTPUT); 
        
    }

    void blink(){
        digitalWrite(13,HIGH);
    }

   
};

#endif
