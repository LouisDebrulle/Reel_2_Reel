#ifndef PINS_H
#define PINS_H

// digital pins
const int on_off_pin = 19;
const int start_motor_pin = 20;
const int dir_pin = 21;

// encoder pin
const int encoderPinA = 2;
const int encoderPinB = 3;

// sensor pin
const int sensor_pos_pin = A4;
const int sensor_neg_pin = A5;

// motor pins
const int motor1_out_pin = 9;
const int motor2_out_pin = 10;

const int motor1_control_pin = 6;
const int motor2_control_pin = 7;

const int motor1_dir_pin = 24;
const int motor2_dir_pin = 26;

const int motor1_energize_pin = 28;
const int motor2_energize_pin = 30;

const int led_pin = 13;

#endif // PINS_H