/*
 * RepRap Ltd Robot Components
 * 
 * Servo controller class
 * Adrian Bowyer
 * 
 * 31 March 2021
 * Licence: GPL
 * 
 * https://reprapltd.com
 * 
 */

#ifndef RRLSERVO_H
#define RRLSERVO_H

#include "Encoder.h"

enum State {antiClockwise, stopped, clockwise};
const int goClockwise = 1;                      // What to write to the motor to make the output go clockwise

class RRLServo
{
  public:
    RRLServo(int pwmP, int dirP, Encoder* enc);

    void Spin();

    void SetTarget(float t);
    void SetProportionalWeight(float w);
    void SetIntegralWeight(float w);
    void SetDerivativeWeight(float w);
    void SetDeadZone(float dz);
    void SetMaximumPWM(int maxP);
    void EStop();
    void Reset();
    void ResetPID();
    float Angle();
    void PrintState();
    void Clockwise(float seconds);
    void AntiClockwise(float seconds);

  private:

    void GoClockwise();
    void GoAntiClockwise();
    void SetSpeed();
    void Stop();
    
    Encoder* encoder;
    float target;                                   // The target angle in radians
    float angle;                                    // Where we are
    int pwm;                                        // The motor PWM value
    float pid;                                      // The currect pid value
    float integral;                                 // The current PID integral
    float lastError;                                // The last error
    float proportionalWeight;                       // The PID P weight
    float integralWeight;                           // The PID I weight
    float derivativeWeight;                         // The PID D weight
    float deadZone;                                 // Close enough (radians)
    unsigned long lastTime;                         // Last time the PID controller was called
    int maxPWM;                                     // Fastest we are allowed to go
    bool eStop;                                     // Emergency stop    
    State state;                                    // What we are doing
    float averageTime;
    
    int pwmPin;
    int directionPin;
};


inline void RRLServo::SetProportionalWeight(float w)
{
  proportionalWeight = w;
  ResetPID();
}

inline void RRLServo::SetIntegralWeight(float w)
{
  integralWeight = w;
  ResetPID();
}

inline void RRLServo::SetDerivativeWeight(float w)
{
  derivativeWeight = w;
  ResetPID();
}

inline void RRLServo::SetDeadZone(float dz)
{
  deadZone = dz;
  ResetPID();
}

inline void RRLServo::SetMaximumPWM(int maxP)
{
  maxPWM = maxP;
  ResetPID();
}

inline void RRLServo::Reset()
{
  eStop = false;
  ResetPID();
}

inline float RRLServo::Angle()
{
  return angle;
}

#endif
