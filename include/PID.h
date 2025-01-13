
#ifndef PID_h
#define PID_h

#include "Arduino.h"
#include <math.h>

class PID {
public:
float kp=0;
    float ki=0;
    float kd=0;
    float outMax=0;
    float outMin=0;

    double pos_des = 0;
    double u_des = 0;

    float cumError=0;
    float lastError=0;
    long previousTime=0;

    PID(float kp_, float ki_, float kd_, float outMin_, float outMax_) {
      kp = kp_;
      ki = ki_;
      kd_= kd_;
      outMax=outMax_;
      outMin=outMin_;
    }

    float output(float setpoint, float mes, long time);
    double spring_curve(double pos);
    void innit();
    

};


float PID::output(float setpoint, float mes, long time)
{

  long currentTime = time;
  float elapsedTime = (currentTime - previousTime);
  float error = (setpoint - mes);
  cumError = cumError + error * elapsedTime;
  float dDifferentialStep = (error - lastError) / elapsedTime;

  float e = kp * error + ki * cumError  + kd * dDifferentialStep;
  float u_des = spring_curve(setpoint);
  float out = e + u_des;
  
   if (out > outMax) {out = outMax;}
  else if (out < outMin) {out = outMin;}
  
  lastError = error;
  previousTime = currentTime;
  return out;
}


double PID::spring_curve(double pos){
  double m = 5;
  double c = -14.05;
  return m*pos +c;
}

void PID::innit(){
  cumError=0;
  lastError=0;
  previousTime=0;
}


#endif 