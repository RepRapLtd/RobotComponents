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

#include "RRLServo.h"

RRLServo::RRLServo(int pwmP, int dirP, Encoder* enc)
{
  directionPin = dirP;
  pwmPin = pwmP;
  encoder = enc;
  
  TCCR2B = TCCR2B & B11111000 | B00000001; // Set PWM for D3 & D11 to 31 kHz
  pinMode(directionPin, OUTPUT);
  digitalWrite(directionPin, 0);   
  pinMode(pwmPin, OUTPUT);
  digitalWrite(pwmPin, 0);
  Stop();
  angle = encoder->Angle();
  target = angle;
  proportionalWeight = 1.0;
  integralWeight = 0.0;
  derivativeWeight = 0.0;
  deadZone = 0.05;
  maxPWM = 50;
  eStop = false;
  averageTime = 0.0;
  ResetPID(); 
}


void RRLServo::Spin()
{
  if(eStop)
  {
    Stop();
    return;
  }

  angle = encoder->Angle();
  float error = target - angle;
  
  if(fabs(error) < deadZone)
  {
    Stop();
    return;
  }

  unsigned long now = micros();
  float dT = (float)(now - lastTime)*0.000001;
  averageTime = (averageTime*9.0 + dT)*0.1;
  integral += error*dT;
  float derivative = (error - lastError)/dT;
  
  lastError = error;
  lastTime = now;
  
  pid = proportionalWeight*error + integralWeight*integral + derivativeWeight*derivative; 
 
  float absPID = fabs(pid);
  pwm = round(absPID);
  if(pwm > maxPWM)
  {
    pwm = maxPWM;
  }
  
  if(pid < 0.0 && (state == clockwise || state == stopped))
  {
    GoAntiClockwise();
  } else if(pid > 0.0 && (state == antiClockwise || state == stopped))
  {
    GoClockwise();
  } else
  {
    SetSpeed();   
  }  
}

void RRLServo::ResetPID()
{
  integral = 0.0;
  lastTime = micros();
  lastError = 0.0;
}

void RRLServo::SetTarget(float t)
{
  target = t;
  ResetPID();
}


void RRLServo::PrintState()
{
  Serial.println("\n Current state:");
  Serial.print("  Encoder reading: ");
  Serial.println(encoder->Reading());
  Serial.print("  Angle: ");
  Serial.print(angle, 4);
  Serial.print(" radians (");
  Serial.print(angle*180.0/PI, 4);
  Serial.println(" degrees)");
  Serial.print("  Target angle: ");
  Serial.print(target, 4);
  Serial.print(" radians, (");
  Serial.print(target*180.0/PI, 4);
  Serial.println(" degrees)");
  Serial.print("  Dead zone (radians): ");
  Serial.println(deadZone, 4);
  Serial.print("  Current PID: ");
  Serial.println(pid, 4);
  Serial.print("  Proportional weight: ");
  Serial.println(proportionalWeight, 4);
  Serial.print("  Integral weight: ");
  Serial.println(integralWeight, 4);
  Serial.print("  Derivative weight: ");
  Serial.println(derivativeWeight, 4);
  Serial.print("  Maximum PWM: ");
  Serial.println(maxPWM);
  Serial.print("  Rolling average dT (mS): ");
  Serial.println(averageTime*1000.0, 4);  
  Serial.print("  State is: ");
  switch(state)
  {
    case antiClockwise:
      Serial.println("anticlockwise");
      break;
    case stopped:
      Serial.println("stopped");
      break;
    case clockwise:
      Serial.println("clockwise");
      break;      
  }
  if(eStop)
   Serial.println("  Emergency stopped!");
  Serial.println();    
}

// Motor control

void RRLServo::GoClockwise()
{
  digitalWrite(pwmPin, 0);
  digitalWrite(directionPin, goClockwise);
  delay(1);
  analogWrite(pwmPin, pwm);
  state = clockwise; 
}

void RRLServo::GoAntiClockwise()
{
  digitalWrite(pwmPin, 0);
  digitalWrite(directionPin, 1 - goClockwise);
  delay(1);
  analogWrite(pwmPin, pwm);
  state = antiClockwise;  
}

void RRLServo::SetSpeed()
{
  analogWrite(pwmPin, pwm);
}

void RRLServo::Stop()
{
  analogWrite(pwmPin, 0);
  state = stopped;  
}

void RRLServo::Clockwise(float seconds)
{
  if(eStop)
    return;
  eStop = true;
  int oldPWM = pwm;
  pwm = maxPWM/2;
  GoClockwise();
  delay((long)(seconds*1000.0));
  Stop();
  angle = encoder->Angle();
  target = angle;
  pwm = oldPWM;
  Reset();    
}

void RRLServo::AntiClockwise(float seconds)
{
  if(eStop)
    return;
  eStop = true;
  int oldPWM = pwm;
  pwm = maxPWM/2;
  GoAntiClockwise();
  delay((long)(seconds*1000.0));
  Stop();
  angle = encoder->Angle();
  target = angle;
  pwm = oldPWM;
  Reset();    
}

void RRLServo::EStop()
{
  eStop = true;
  Stop();
}
