#include <Arduino.h>

#include "linear_speed_curve.h"
#include "state_machine.h"
#include "board.h"


unsigned long lDt = 100;
const int status_pin = 18;
const int encoderPinA = 2;
const int encoderPinB = 3;
const int pwmPin = 5;




 

Board _board(encoderPinA, encoderPinB, pwmPin);
state_machine kernel(_board);

double times[] = {10*1e3, 50*1e3}; 
double speeds[] = {700, 300};                                                     
lin_speed_curve _speed_curve(times, speeds, 2); 



void encoder_step() {
 _board._encoder.step();
}

void check_status(){
  kernel.change_state(); 
}



void setup() {

Serial.begin(9600);
_board.init();

attachInterrupt(digitalPinToInterrupt(encoderPinA), encoder_step, RISING);
attachInterrupt(digitalPinToInterrupt(status_pin), check_status, CHANGE);

}
  




void loop() {

  kernel.step();

  double time = millis();
  double speed =_board._encoder.get_speed();
  int duty_cycle = _speed_curve.getSpeedAtTime(time);

  Serial.print(time);
  Serial.print(" ,");
  Serial.print(duty_cycle);
  Serial.print(" ,");
  Serial.println(speed);

   _board._pwm.set_dc(duty_cycle);

  delay(lDt);
}
