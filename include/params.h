#ifndef PARAMS_H
#define PARAMS_H

#include "linear_curve.h"

// sampling time
unsigned long lDt = 100*1e3;

//filter size
const int filter_size = 30;

//Speed- and Torque Motor params
const int MAX_SPEED = 5;
const int gear_ratio = 100;
const int MAX_TORQUE = 100; 
double des_pos = 15; // max25
double start_pos = 10; // max 25
double speed_des = 2;
double radius_ratio = 30.0/57.0;
double motor_speed = speed_des*radius_ratio*gear_ratio;

//Speed and Break curves
double times[] = {0, 10};
double speed_points[] = {0, 100};
double break_points[] = {100, start_pos};

lin_curve _speed_curve(times, speed_points, sizeof(times)/sizeof(times[0])); 
lin_curve _breake_curve(times, break_points, sizeof(times)/sizeof(times[0]));

#endif 