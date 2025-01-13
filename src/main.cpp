#include <Arduino.h>
#include <TimerOne.h>

#include "linear_curve.h"
#include "state_machine.h"
#include "board.h"
#include "pin.h"
#include "mv_average_filter.h"
#include "PID.h"
#include "speed_motor.h"
#include "brake_motor.h"


unsigned long lDt = 100*1e3;
const int filter_size = 30;

const int MAX_SPEED = 5;
const int gear_ratio = 100;
const int MAX_TORQUE = 100;
double des_pos = 10;
double start_pos = 8.7;

double speed_des = 200;
double radius_ratio = 30.0/57.0;
double motor_speed = speed_des*radius_ratio;

Board _board;
Speed_motor speed_motor(_board, MAX_SPEED*gear_ratio);
Breake_motor breake_motor(_board, MAX_TORQUE);

PID _pid(0.05,0.001,0,0, 90);
state_machine kernel(_board);

//double times[] = {0, 20*1e3, 20*1e3, 30*1e3, 30*1e3, 40*1e3, 40*1e3, 50*1e3, 50*1e3, 60*1e3, 60*1e3, 70*1e3, 70*1e3, 80*1e3}; 
//double breaks[] = {20, 20, 30, 30, 40, 40, 50, 50, 60, 60, 70, 70, 80, 80};
double times[] = {0, 5*1e3, 5*1e3, 10*1e3, 10*1e3, 15*1e3, 15*1e3, 20*1e3, 20*1e3, 25*1e3, 25*1e3, 30*1e3, 30*1e3, 35*1e3, 35*1e3, 40*1e3, 40*1e3, 45*1e3, 45*1e3, 50*1e3}; 
double breaks[] = {20, 20, 30, 30, 20, 20, 40, 40, 20, 20, 50, 50, 20, 20, 60, 60, 20, 20, 70, 70};  
double speeds[] = {100, 100};
                                                  
lin_curve _speed_curve(times, speeds, sizeof(times)/sizeof(times[0])); 
lin_curve _breake_curve(times, breaks, sizeof(times)/sizeof(times[0]));
mv_average_filter speed_filter(filter_size);


void encoder_step() {
 _board._encoder.step();
}

void check_status(){
  kernel.change_state(); 
}

void motor_feedback(){
  speed_motor.measure_feedback();
}

void change_direction(){
  if (kernel.state != off)
  {
  speed_motor.change_direction();
  breake_motor.change_direction();
  }
  
  
}




 void main_loop(){

  switch (kernel.state)
  {
  case off:
    digitalWrite(led_pin, LOW);
    speed_motor.enable();
    breake_motor.enable();
    _board.init();
    break;


  case on:
    digitalWrite(led_pin, HIGH);
    
    speed_motor.init();
    breake_motor.init();
    _pid.innit();
    _board.init();
    speed_filter.init();
    breake_motor.set(breake_motor.get_dc(_pid.spring_curve(start_pos)));
    Serial.println(_board._pos_sensor.get_pos());
    break;

  case running:
    double time = kernel.get_time();
    double speed =_board._encoder.get_speed();
    speed_filter.push(speed);
    double speed_smooth = speed_filter.get_average();
    
    double pos = _board._pos_sensor.get_pos();


    //double breake_des = _breake_curve.get(time);
    double breake_des = _pid.output(des_pos, pos, time);
    //double speed_des = _speed_curve.get(time);
    

    int input_speed = speed_motor.get_dc(motor_speed);
    int input_breake = breake_motor.get_dc(breake_des);
    speed_motor.set(int(input_speed));
    breake_motor.set(int(input_breake));


    
    Serial.print(time/1000);
    Serial.print(" ,");
    Serial.print(speed_des/100);
    Serial.print(" ,");
    Serial.print(speed_smooth, 4);
    Serial.print(" ,");
    Serial.print(double(input_speed)/ICR4 *100);
    Serial.print(" ,");
    Serial.print(double(input_breake)/ICR4 *100);
    Serial.print(" ,");
    Serial.print(des_pos);
    Serial.print(" ,");
    Serial.println(pos);
    
    break;
  }
 
  
};


void setup() {
Serial.begin(9600);
Timer1.initialize(lDt); 
Timer1.attachInterrupt(main_loop);

_board.init();
kernel.change_state();
attachInterrupt(digitalPinToInterrupt(encoderPinA), encoder_step, RISING);
attachInterrupt(digitalPinToInterrupt(on_off_pin), check_status, CHANGE);
attachInterrupt(digitalPinToInterrupt(start_motor_pin), check_status, CHANGE);
attachInterrupt(digitalPinToInterrupt(dir_pin), change_direction, CHANGE);

}
 
 



void loop() {

}
