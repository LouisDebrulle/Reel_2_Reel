#include <Arduino.h>
#include <TimerOne.h>

#include "linear_speed_curve.h"
#include "state_machine.h"
#include "board.h"
#include "pin.h"
#include "mv_average_filter.h"
#include "PID.h"


unsigned long lDt = 100*1e3;
const int filter_size = 10;

Board _board;
Motor _motor1(_board);
PID _pid(100,0.01,0,0, 10000);
state_machine kernel(_board);

double times[] = {0, 10*1e3};//{0, 10*1e3, 10*1e3, 20*1e3, 20*1e3, 30*1e3, 30*1e3, 40*1e3}; 
double speeds[] = {1,1}; //{0.3, 0.3, 0.6, 0.6, 0.8, 0.8, 1, 1};                                                     
lin_speed_curve _speed_curve(times, speeds, sizeof(times)/sizeof(times[0])); 

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
    double speed_smooth = speed_filter.get_average();
    
    double speed_des = _speed_curve.getSpeedAtTime(time);
    //float dc = _pid.output(speed_des, speed_smooth);
    int dc = _motor1.get_dc(speed_des);
    _motor1.set_speed(int(dc), 0);

    double pos = _board._pos_sensor.get_pos();

    Serial.print(time/1000);
    Serial.print(" ,");
    Serial.print(speed_des);
    Serial.print(" ,");
    Serial.print(speed_smooth);
    Serial.print(" ,");
    Serial.print(double(dc)/ICR4 *100); // 
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
