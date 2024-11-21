#include <Arduino.h>

#include "linear_speed_curve.h"
#include "state_machine.h"
#include "board.h"
#include "pin.h"


unsigned long lDt = 100;









 

Board _board;
Motor _motor1(_board);
Motor _motor2(_board);

state_machine kernel;

double times[] = {0, 50*1e3}; 
double speeds[] = {700, 300};                                                     
lin_speed_curve _speed_curve(times, speeds, 2); 



void encoder_step() {
 _board._encoder.step();
}

void check_status(){
  kernel.change_state(_board); 
}



void setup() {

Serial.begin(9600);
_board.init();
attachInterrupt(digitalPinToInterrupt(on_off_pin), check_status, CHANGE);
attachInterrupt(digitalPinToInterrupt(encoderPinA), encoder_step, RISING);



}
  
void main_loop(){


  double time = millis();
  double speed =_board._encoder.get_speed();
  int duty_cycle = _speed_curve.getSpeedAtTime(time);
  _motor1.set_speed(300);

  Serial.print(time);
  Serial.print(" ,");
  Serial.print(duty_cycle);
  Serial.print(" ,");
  Serial.println(speed);

   

  delay(lDt);
};



void loop() {


  if (kernel.step())
  {
    main_loop();
  }
  
  
}
