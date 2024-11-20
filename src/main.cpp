#include <Arduino.h>

#include "pwm.h"
#include "Encoder.h"
#include "linear_speed_curve.h"
#include "state_machine.h"

const int A_pin = 2;
const int B_pin = 3;
const int pwm_pin = 5;
const int status_pin = 18;
const const int pulses_per_rev = 2048;

struct Board {
    Encoder _encoder = Encoder(2, 3);

}_board;


 




unsigned long last_pulse_time = 0;
unsigned long pulse_interval = 0;
int direction = 1;
double last_speed = 0;

unsigned long lDt = 100;

Encoder _encoder(A_pin, B_pin);
state_machine kernel;

double times[] = {10*1e3, 50*1e3}; 
double speeds[] = {700, 300};                                                     
lin_speed_curve _speed_curve(times, speeds, 2); 
pwm_tim_1 _pwm(pwm_pin);


void encoder_step() {
 _encoder.step();
}

void check_status(){
  kernel.change_state(); 
}



void setup() {

_pwm.innit();
pinMode(13, OUTPUT);
attachInterrupt(digitalPinToInterrupt(A_pin), encoder_step, RISING);
attachInterrupt(digitalPinToInterrupt(status_pin), check_status, CHANGE);
Serial.begin(9600);
}
  




void loop() {

  kernel.step();
  double time = millis();
  double speed =_encoder.get_speed();
 
  
  int duty_cycle = _speed_curve.getSpeedAtTime(time);

  Serial.print(time);
  Serial.print(" ,");
  Serial.print(duty_cycle);
  Serial.print(" ,");
  Serial.println(speed);

  OCR3A = 300;

  delay(lDt);
}
