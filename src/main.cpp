#include <Arduino.h>
#include <TimerOne.h>

#include "linear_speed_curve.h"
#include "state_machine.h"
#include "board.h"
#include "pin.h"


unsigned long lDt = 100*1e3;

Board _board;
Motor _motor1(_board);

state_machine kernel(_board);

double times[] = {0, 50*1e3}; 
double speeds[] = {300, 200};                                                     
lin_speed_curve _speed_curve(times, speeds, 2); 



void encoder_step() {
 _board._encoder.step();
}

void check_status(){
  kernel.change_state(); 
}

void start_motor() {
  // kernel.change_state()
}


 void main_loop(){

  if (kernel.step())
  {
  double time = kernel.get_time();
  int pulse_count = _board._encoder.get_puls_count();
  int pulse_sum = _board._encoder.get_puls_sum();
  double speed =_board._encoder.get_speed();
  
  int duty_cycle = _speed_curve.getSpeedAtTime(time);
  _motor1.set_speed(duty_cycle, duty_cycle);

  Serial.print(time/1000);
  Serial.print(" ,");
  Serial.print(double(duty_cycle)/100.0);
  Serial.print(" ,");
  Serial.print(speed);
  Serial.print(" ,");
  Serial.print(pulse_count);
  Serial.print(" ,");
  Serial.println(_board._encoder.get_pulse_interval());
  }
  
};


void setup() {
Serial.begin(9600);
Timer1.initialize(lDt); 
Timer1.attachInterrupt(main_loop);

_motor1.init();
_board.init();

attachInterrupt(digitalPinToInterrupt(encoderPinA), encoder_step, RISING);
attachInterrupt(digitalPinToInterrupt(on_off_pin), check_status, CHANGE);
attachInterrupt(digitalPinToInterrupt(start_motor_pin), start_motor, RISING);
}
 
 




void loop() {

}
