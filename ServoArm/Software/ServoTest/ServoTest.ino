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

#include "RRLServo.h"

const int pWMPin = 11;                          // Motor PWM in
const int dirPin = 13;                          // Motor direction
const int selectPin = 6;                        // Select the AS5040
const int clockPin = 7;                         // AS5040 clock
const int dataPin = 2;                          // AS5040 data

Encoder* encoder;
RRLServo* servo;

//***********************************************************************************



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
  encoder = new Encoder(dataPin, clockPin, selectPin);
  servo = new RRLServo(pWMPin, dirPin, encoder);
  Serial.begin(9600);
  Serial.setTimeout(100000);
  Prompt();
}




void loop()
{
  servo->Spin();

  float x;
  
  if(Serial.available() > 0)
  {   
    char c = (char)Serial.read();
    switch(c)
    {
     case 's':
      servo->PrintState();
      break;

     case 'e':
      servo->EStop();
      Serial.println("Emergency stop!");
      break;

     case 'r':
      Serial.println("Emergency stop reset.");
      servo->Reset();
      break;

     case 'p':
      x = Serial.parseFloat(SKIP_WHITESPACE);
      Serial.print("Proportional weight set to ");
      Serial.println(x);
      servo->SetProportionalWeight(x);
      break;

     case 'i':
      x = Serial.parseFloat(SKIP_WHITESPACE);
      servo->SetIntegralWeight(x);
      Serial.print("Integral weight set to ");
      Serial.println(x);
      break;   

     case 'd':
      x = Serial.parseFloat(SKIP_WHITESPACE);
      Serial.print("Derivative weight set to ");
      servo->SetDerivativeWeight(x);
      Serial.println(x);
      break;

     case '0':
      x = Serial.parseFloat(SKIP_WHITESPACE);
      Serial.print("Deadzone set to ");
      Serial.println(x);
      servo->SetDeadZone(x);
      break;

     case 't':
      x = Serial.parseFloat(SKIP_WHITESPACE);
      Serial.print("Target set to ");
      Serial.print(x);
      x = x*PI/180.0;     
      Serial.print(" degrees (");
      Serial.print(x);
      Serial.println(" radians).");
      servo->SetTarget(x);
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
