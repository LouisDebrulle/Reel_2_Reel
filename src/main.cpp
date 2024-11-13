#include <Arduino.h>

#include "pwm.h"
#include "Encoder.h"
#include "linear_speed_curve.h"

int A_pin = 2;
int B_pin = 3;
int pwm_pin = 5;

const int pulses_per_rev = 2048;
unsigned long last_pulse_time = 0;
unsigned long pulse_interval = 0;
int direction = 1;
double last_speed = 0;

unsigned long lDt = 100;

Encoder _encoder(A_pin, B_pin);
// pwm_tim_1 _pwm(pwm_pin);

double times[] = {10*1e3, 20*1e3, 30*1e3}; // Time points in seconds
double speeds[] = {0, 10, 10}; // Speed points (e.g., rpm)
lin_speed_curve _speed_curve(times, speeds, 3); // Create the speed curve



void encoder_step() {
  unsigned long current_time = micros();
  pulse_interval = current_time - last_pulse_time;
  last_pulse_time = current_time;

  if (digitalRead(B_pin) == HIGH) {
    direction = 1;
  } else {
    direction = -1;
  }
}

void setup() {

  pinMode(pwm_pin, OUTPUT);

  TCCR3A = _BV(COM3A1) | _BV(WGM31);
  TCCR3B = _BV(WGM33) | _BV(WGM32) | _BV(CS30);
  ICR3 = 799;
  OCR3A = 300;

  attachInterrupt(digitalPinToInterrupt(A_pin), encoder_step, RISING);
  Serial.begin(9600);
}
  

void loop() {
  double time = millis();
  double speed;
  if (pulse_interval != 0) {
    speed = (60.0 * 1e6) / (double(pulses_per_rev) * pulse_interval);
    speed *= direction;
  } else {
    speed = 0;
  }

  double currentSpeed = _speed_curve.getSpeedAtTime(time);

  Serial.print(time);
  Serial.print(" ,");
  Serial.println(currentSpeed);

  OCR3A = currentSpeed;

  delay(lDt);
}
