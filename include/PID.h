
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

    double out;
    double offset;

    PID(float kp_, float ki_, float kd_, float outMin_, float outMax_) {
      kp = kp_;
      ki = ki_;
      kd_= kd_;
      outMax=outMax_;
      outMin=outMin_;

      out = 0,
      offset = 0;
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

  out = e+offset;
  
   if (out > outMax) {out = outMax;}
  else if (out < outMin) {out = outMin;}
  
  lastError = error;
  previousTime = currentTime;
  return out;
}



void PID::innit(){
  cumError=0;
  lastError=0;
  previousTime=0;

  offset = out;
  out = 0;
}


#endif 