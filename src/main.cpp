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
#include "params.h"
#include "reel_2_reel_sys.h"


Board _board;
Speed_motor speed_motor(_board, MAX_SPEED*gear_ratio);
Breake_motor breake_motor(_board, MAX_TORQUE);

state_machine kernel(_board);
reel_2_reel_sys reel_2_reel;
PID _pid(0,0.005,0,0, 90); //0.05,0.001,0,0, 90

mv_average_filter speed_filter(filter_size);


void encoder_step() {
 _board._encoder.step();
}

void change_state(){
  kernel.change_state(); 
  speed_motor.init();
    breake_motor.init();
    _pid.innit();
    _board.init();
    speed_filter.init();
}

void motor_feedback(){
  speed_motor.measure_feedback();
}

void change_direction(){
  if (kernel.state != off)
  {
  speed_motor.change_direction();
  //breake_motor.change_direction();
  }
}

void print_results(double time, double speed_des, double speed_smooth, double input_speed, double input_breake, double des_pos, double pos){
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
}




 void main_loop(){

  switch (kernel.state)
  {
  case off:{
    digitalWrite(led_pin, LOW);
    speed_motor.enable();
    breake_motor.enable();
    // _pid.offset = 0;

    break;

  }
    


  case on:{
    digitalWrite(led_pin, HIGH);
    double time = kernel.get_time();

    double breake_des_start_pos = _pid.output(start_pos, _board._pos_sensor.get_pos(), time);
    int input_breake_start_pos = breake_motor.get_dc(breake_des_start_pos);
    breake_motor.set(int(input_breake_start_pos));
    
    print_results(millis()-kernel.start_time, 0, 0, 0, input_breake_start_pos, start_pos, _board._pos_sensor.get_pos());
    

    break;
  }
    

  case running:{
    double time = kernel.get_time();
    double speed =_board._encoder.get_speed();
    speed_filter.push(speed);
    double speed_smooth = speed_filter.get_average();
    
    double pos = _board._pos_sensor.get_pos();

    double breake_des = _pid.output(des_pos, pos, time);    

    int input_speed = speed_motor.get_dc(motor_speed);
    int input_breake = breake_motor.get_dc(breake_des);
    speed_motor.set(int(input_speed));
    breake_motor.set(int(input_breake));


    print_results(millis()-kernel.start_time, speed_des, speed_smooth, input_speed, input_breake, des_pos, pos);
    break;
    }
  }
 
  
};


void setup() {
Serial.begin(9600);
Timer1.initialize(lDt); 
Timer1.attachInterrupt(main_loop);

_board.init();
kernel.change_state();
reel_2_reel.rest_pos = _board._pos_sensor.get_pos();

attachInterrupt(digitalPinToInterrupt(encoderPinA), encoder_step, RISING);
attachInterrupt(digitalPinToInterrupt(on_off_pin), change_state, CHANGE);
attachInterrupt(digitalPinToInterrupt(start_motor_pin), change_state, CHANGE);
attachInterrupt(digitalPinToInterrupt(dir_pin), change_direction, CHANGE);

}
 
 



void loop() {

}
