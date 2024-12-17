
#ifndef PID_h
#define PID_h

#include "Arduino.h"
#include <math.h>

class PID {
public:
    PID(float kp, float ki, float kd, float outMin, float outMax) {
      kp_ = kp;
      ki_ = ki;
      kd_ = kd;
      outMax_=outMax;
      outMin_=outMin;
    }

    void resetParam(float kp, float ki, float kd);
    float output(float w, float y);
    void wirtData(float OutVal, float w, bool ControlEN);
    static float setpointZelle(float w);
    static float setpointKuelbox(float w);

    float kp_=0;
    float ki_=0;
    float kd_=0;
    float outMax_=0;
    float outMin_=0;

    float cumError=0;
    float lastError=0;
    long previousTime=0;

};



void PID::resetParam(float kp, float ki, float kd)
{
  kp_ = kp;
  ki_ = ki;
  kd_ = kd;
}

float PID::output(float w, float y)
{

  long currentTime = millis();
  float elapsedTime = (currentTime - previousTime);
  float error = (w - y);
  float dIntegralStep = error * elapsedTime;
  float dDifferentialStep = (error - lastError) / elapsedTime;

  float out = kp_ * error + ki_ * (dIntegralStep + cumError) + kd_ * dDifferentialStep;
  

  
   if (out > outMax_)
  {
    Serial.print("max : ");
    out = outMax_;
  }
  else if (out < outMin_)
  {
    Serial.println("min");
    out = outMin_;
  }
  
 
 
  lastError = error;
  previousTime = currentTime;
  return out;
}


#endif // PID_CPP