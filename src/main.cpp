#include <Arduino.h>
#include <TimerOne.h>

#include "linear_speed_curve.h"
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
const int MAX_TORQUE = 10;

Board _board;
Speed_motor speed_motor(_board, MAX_SPEED*gear_ratio);
Breake_motor breake_motor(_board, MAX_TORQUE);

PID _pid(100,0.01,0,0, 10000);
state_machine kernel(_board);

double times[] = {0, 10*1e3}; //{0, 10*1e3, 10*1e3, 20*1e3, 20*1e3, 30*1e3, 30*1e3, 40*1e3, 40*1e3, 50*1e3}; 
double speeds[] = {100, 100}; //{20, 20, 40, 40, 60, 60, 80, 80, 100, 100};                                                     
lin_speed_curve _speed_curve(times, speeds, sizeof(times)/sizeof(times[0])); 

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
  speed_motor.change_direction();
  breake_motor.change_direction();
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
    digitalWrite(_board.motor1.energize_pin, HIGH);
    digitalWrite(_board.motor2.energize_pin, HIGH);
    _board.init();
    speed_filter.init();

    break;

  case running:
    double time = kernel.get_time();
    double speed =_board._encoder.get_speed();
    speed_filter.push(speed);
    double speed_smooth = speed_filter.get_average();
    
    double speed_des = _speed_curve.getSpeedAtTime(time);
    double motor_fb_speed = speed_motor.get_feedback();
    //float dc = _pid.output(speed_des, speed_smooth);
    int dc = speed_motor.get_dc(speed_des);
    speed_motor.set(int(dc));

    double pos = _board._pos_sensor.get_pos();

    
    Serial.print(time/1000);
    Serial.print(" ,");
    Serial.print(speed_des/100);
    Serial.print(" ,");
    Serial.print(speed, 4);
    Serial.print(" ,");
    Serial.println(speed_smooth);
    
    
    //Serial.print(double(dc)/ICR4 *100); // 
    
    
   
    break;
  }
 
  
};


void setup() {
Serial.begin(9600);
Timer1.initialize(lDt); 
Timer1.attachInterrupt(main_loop);

speed_motor.init();
_board.init();
kernel.change_state();
attachInterrupt(digitalPinToInterrupt(encoderPinA), encoder_step, RISING);
attachInterrupt(digitalPinToInterrupt(on_off_pin), check_status, CHANGE);
attachInterrupt(digitalPinToInterrupt(start_motor_pin), check_status, CHANGE);
attachInterrupt(digitalPinToInterrupt(dir_pin), change_direction, CHANGE);

while (digitalRead(on_off_pin) || digitalRead(start_motor_pin) )
{
  Serial.println("power off");
  delay(1000);
}

}
 
 




void loop() {

}
