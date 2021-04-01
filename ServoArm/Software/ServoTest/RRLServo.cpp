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
  integral = 0.0;
  proportionalWeight = 1.0;
  integralWeight = 0.0;
  derivativeWeight = 0.0;
  deadZone = 0.05;
  lastTime = micros();
  maxPWM = 50;
  eStop = false;  
}


void RRLServo::Spin()
{
  if(eStop)
  {
    Stop();
    return;
  }

  angle = encoder->Angle();
  unsigned long now = micros();
  float dA = target - angle;
  float absDA = fabs(dA);
  float dT = (float)(now - lastTime)*0.000001;
  integral += dA*dT;
  float derivative = (dA - lastDA)/dT;
  lastDA = dA;
  lastTime = now;
  pid = proportionalWeight*dA + integralWeight*integral + derivativeWeight*derivative; 

  if(absDA < deadZone)
  {
    Stop();
    return;
  }
  
  float absPID = fabs(pid);
  pwm = round(absPID);
  if(pwm > maxPWM)
  {
    pwm = maxPWM;
  }
  
  if(pid < 0.0 && state == clockwise)
  {
    GoAntiClockwise();
  } else if(pid > 0.0 && state == antiClockwise)
  {
    GoClockwise();
  } else
  {
    SetSpeed();   
  }  
}


void RRLServo::PrintState()
{
  Serial.println("\n Current state:");
  Serial.print("  Encoder reading: ");
  Serial.println(encoder->Reading());
  Serial.print("  Angle: ");
  Serial.print(angle);
  Serial.print(" radians (");
  Serial.print(angle*180.0/PI);
  Serial.println(" degrees)");
  Serial.print("  Target angle: ");
  Serial.print(target);
  Serial.print(" radians, (");
  Serial.print(target*180.0/PI);
  Serial.println(" degrees)");
  Serial.print("  Dead zone (radians): ");
  Serial.println(deadZone);
  Serial.print("  Current PID: ");
  Serial.println(pid);
  Serial.print("  Proportional weight: ");
  Serial.println(proportionalWeight);
  Serial.print("  Integral weight: ");
  Serial.println(integralWeight);
  Serial.print("  Derivative weight: ");
  Serial.println(derivativeWeight);
  Serial.print("  Maximum PWM: ");
  Serial.println(maxPWM);
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
