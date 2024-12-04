#include <Arduino.h>
#include <TimerOne.h>

#include "linear_speed_curve.h"
#include "state_machine.h"
#include "board.h"
#include "pin.h"
#include "mv_average_filter.h"


unsigned long lDt = 100*1e3;
const int filter_size = 10;

Board _board;
Motor _motor1(_board);

state_machine kernel(_board);

double times[] = {0, 50*1e3}; 
double speeds[] = {5000, 5000};                                                     
lin_speed_curve _speed_curve(times, speeds, 2); 

mv_average_filter<double,filter_size> speed_filter;


void encoder_step() {
 _board._encoder.step();
}

void check_status(){
  kernel.change_state(); 
}




 void main_loop(){

  switch (kernel.state)
  {
  case off:
    digitalWrite(13, LOW);
    digitalWrite(_board.motor1.energize_pin, LOW);
    digitalWrite(_board.motor2.energize_pin, LOW);
    _board.init();
    break;


  case on:
    digitalWrite(13, HIGH);
    digitalWrite(_board.motor1.energize_pin, HIGH);
    digitalWrite(_board.motor2.energize_pin, HIGH);
    _board.init();
    break;

  case running:
    double time = kernel.get_time();
    double speed =_board._encoder.get_speed();
    speed_filter.push(speed);
    
    int duty_cycle = _speed_curve.getSpeedAtTime(time);
    _motor1.set_speed(duty_cycle, duty_cycle);

    double pos = _board._pos_sensor.get_pos();

    Serial.print(time/1000);
    Serial.print(" ,");
    Serial.print(double(duty_cycle)/ICR4*100);
    Serial.print(" ,");
    Serial.print(speed_filter.get_average());
    Serial.print(" ,");
    Serial.println(pos);
    break;
  }
 
  
};


void setup() {
Serial.begin(9600);
Timer1.initialize(lDt); 
Timer1.attachInterrupt(main_loop);

_motor1.init();
_board.init();
kernel.change_state();
attachInterrupt(digitalPinToInterrupt(encoderPinA), encoder_step, RISING);
attachInterrupt(digitalPinToInterrupt(on_off_pin), check_status, CHANGE);
attachInterrupt(digitalPinToInterrupt(start_motor_pin), check_status, CHANGE);

while (digitalRead(on_off_pin) || digitalRead(start_motor_pin) )
{
  Serial.println("power off");
  delay(5000);
}

}
 
 




void loop() {

}
