/*
 * RepRap Ltd Robot Components
 * 
 * Gear-chain Servo Test Program
 * Adrian Bowyer
 * 
 * 29 March 2021
 * Licence: GPL
 * 
 * https://reprapltd.com
 * 
 */

#include "Encoder.h"

const int pWMPin = 11;                          // Motor PWM in
const int dirPin = 13;                          // Motor direction
const int selectPin = 6;                        // Select the AS5040
const int clockPin = 7;                         // AS5040 clock
const int dataPin = 2;                          // AS5040 data
const int goClockwise = 1;                      // What to write to the motor to make the output go clockwise

const float readingToDegrees = 360.0/1024.0;

float target;                                   // The target angle in radians
float integral;                                 // The current PID integral
float lastDA;                                   // The last error
float proportionalWeight;                       // The PID P weight
float integralWeight;                           // The PID I weight
float derivativeWeight;                         // The PID D weight
float deadZone;                                 // Close enough (radians)
unsigned long lastTime;                         // Last time the PID controller was called
int maxPWM;                                     // Fastest we are allowed to go
bool eStop;                                     // Emergency stop

enum State {antiClockwise, stopped, clockwise};
State state;

Encoder* encoder = new Encoder(dataPin, clockPin, selectPin);

//***********************************************************************************

// Motor control

void GoClockwise(int pwm)
{
  digitalWrite(pWMPin, 0);
  digitalWrite(dirPin, goClockwise);
  delay(1);
  analogWrite(pWMPin, pwm);
  state = clockwise; 
}

void GoAntiClockwise(int pwm)
{
  digitalWrite(pWMPin, 0);
  digitalWrite(dirPin, 1 - goClockwise);
  delay(1);
  analogWrite(pWMPin, pwm);
  state = antiClockwise;  
}

void SetSpeed(int pwm)
{
  analogWrite(pWMPin, pwm);
}

void Stop()
{
  analogWrite(pWMPin, 0);
  state = stopped;  
}



float PIDValue(float& absDA)
{
  float angle = encoder->Angle();
  unsigned long now = micros();
  float dA = target - angle;
  absDA = fabs(dA);
  float dT = (float)(now - lastTime)*0.000001;
  integral += dA*dT;
  float derivative = (dA - lastDA)/dT;
  lastDA = dA;
  lastTime = now;
  float pid = proportionalWeight*dA + integralWeight*integral + derivativeWeight*derivative;
  return pid;  
}

void PID()
{
  if(eStop)
  {
    Stop();
    return;
  }

  float absDA;
  float pid = PIDValue(absDA);
  if(absDA < deadZone)
  {
    Stop();
    return;
  }
  
  float absPID = fabs(pid);
  int pwm = round(absPID);
  if(pwm > maxPWM)
  {
    pwm = maxPWM;
  }
  
  if(pid < 0.0 && state == clockwise)
  {
    GoAntiClockwise(pwm);
  } else if(pid > 0.0 && state == antiClockwise)
  {
    GoClockwise(pwm);
  } else
  {
    SetSpeed(pwm);   
  }
}

void PrintState()
{
  Serial.println("\n Current state:");
  int r = encoder->Reading();
  Serial.print("  Angle: ");
  Serial.print(r);
  Serial.print(", (");
  Serial.print((float)r*readingToDegrees);
  Serial.print(" degrees, ");
  Serial.print((float)r*readingToRadians);
  Serial.println(" radians)");
  Serial.print("  Target angle: ");
  Serial.print(target*180.0/PI);
  Serial.print(" deg, ");
  Serial.print(target);
  Serial.println(" radians.");
  Serial.print("  Dead zone (radians): ");
  Serial.println(deadZone);
  Serial.print("  Current PID: ");
  float dummy;
  float p = PIDValue(dummy);
  Serial.println(p);
  Serial.print("  Proportional weight: ");
  Serial.println(proportionalWeight);
  Serial.print("  Integral weight: ");
  Serial.println(integralWeight);
  Serial.print("  Derivative weight: ");
  Serial.println(derivativeWeight);
  Serial.print("  Maximum PWM: ");
  Serial.println(maxPWM);
  if(eStop)
   Serial.println("  Emergency stopped!");
  Serial.println();  
}

void Prompt()
{
  Serial.println("\nRepRap Ltd servo test commands:");
  Serial.println(" e - Emergency stop.");
  Serial.println(" r - reset stop.");
  Serial.println(" t X - set target (X degrees).");
  Serial.println(" s - print state.");
  Serial.println(" p W - Set proportional weight.");
  Serial.println(" i W - Set integral weight.");
  Serial.println(" d W - Set derivative weight.");  
  Serial.println(" 0 X - Set dead zone (radians).");
  Serial.println(" ? - print this list.\n");
}

//*********************************************************************************

void setup()
{
  TCCR2B = TCCR2B & B11111000 | B00000001; // Set PWM for D3 & D11 to 31 kHz
  pinMode(dirPin, OUTPUT);
  digitalWrite(dirPin, 0);   
  pinMode(pWMPin, OUTPUT);
  digitalWrite(pWMPin, 0);

  Stop();
  
  Serial.begin(9600);
  Serial.setTimeout(100000);

  target = encoder->Angle();
  integral = 0.0;
  proportionalWeight = 1.0;
  integralWeight = 0.0;
  derivativeWeight = 0.0;
  deadZone = 0.05;
  lastTime = micros();
  maxPWM = 50;
  eStop = false;
  Prompt();
}




void loop()
{
  PID();

  float deg;
  
  if(Serial.available() > 0)
  {   
    char c = (char)Serial.read();
    switch(c)
    {
     case 's':
      PrintState();
      break;

     case 'e':
      Serial.println("Emergency stop!");
      eStop = true;
      break;

     case 'r':
      Serial.println("Emergency stop reset.");
      eStop = false;
      break;

     case 'i':
      integralWeight = Serial.parseFloat(SKIP_WHITESPACE);
      Serial.print("Integral weight set to ");
      Serial.println(integralWeight);
      break;   

     case 'd':
      derivativeWeight = Serial.parseFloat(SKIP_WHITESPACE);
      Serial.print("Derivative weight set to ");
      Serial.println(derivativeWeight);
      break;

     case '0':
      deadZone = Serial.parseFloat(SKIP_WHITESPACE);
      Serial.print("Deadzone set to ");
      Serial.println(deadZone);
      break;

     case 'p':
      proportionalWeight = Serial.parseFloat(SKIP_WHITESPACE);
      Serial.print("Proportional weight set to ");
      Serial.println(proportionalWeight);
      break;

     case 't':
      deg = Serial.parseFloat(SKIP_WHITESPACE);
      target = deg*PI/180.0;
      Serial.print("Target set to ");
      Serial.print(deg);
      Serial.print(" degrees (");
      Serial.print(target);
      Serial.println(" radians).");
      break;
        
     default:
      Serial.print("Unrecognised command: ");
      Serial.println(c);

     case '?':
      Prompt();
      break;     
    }
    while(Serial.available() > 0) Serial.read();
  }
}
