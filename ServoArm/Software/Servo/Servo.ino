/*
 * RepRap Ltd Robot Components
 * 
 * Servo control program
 * Adrian Bowyer
 * 
 * 29 March 2021
 * Licence: GPL
 * 
 * https://reprapltd.com
 * 
 */

const int pWMPin = 11;                          // Motor PWM in
const int dirPin = 13;                          // Motor direction
const int selectPin = 6;                        // Select the AS5040
const int clockPin = 7;                         // AS5040 clock
const int dataPin = 2;                          // AS5040 data
const int clockwise = 1;                        // What to write to the motor to make the output go clockwise
const float pi = 3.1415926;
const float readingToRadians = 2.0*pi/1024.0;
const float readingToDegrees = 180.0/1024.0;

float target;                                   // The target angle in radians
float integral;                                 // The current PID integral
float lastDA;                                   // The last error
float proportionalWeight;                       // The PID P weight
float integralWeight;                           // The PID I weight
float derivativeWeight;                         // The PID D weight
float deadZone;                                 // Close enough
unsigned long lastTime;                         // Last time the PID controller was called
int maxPWM;                                     // Fastest we are allowed to go
bool eStop;                                     // Emergency stop

enum State {backwards, stopped, forwards};
State state;

//***********************************************************************************

// Motor control

void GoForwards(int pwm)
{
  digitalWrite(pWMPin, 0);
  digitalWrite(dirPin, clockwise);
  delay(1);
  analogWrite(pWMPin, pwm);
  state = forwards; 
}

void GoBackwards(int pwm)
{
  digitalWrite(pWMPin, 0);
  digitalWrite(dirPin, 1 - clockwise);
  delay(1);
  analogWrite(pWMPin, pwm);
  state = backwards;  
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

//*************************************************************************************

// AS5040 magnetic shaft encoder

// Read in a byte of data from the AS5040.

byte ShiftIn(byte data_pin, byte clock_pin)
{
  byte data = 0;

  for (int i=7; i>=0; i--)
  {
    digitalWrite(clock_pin, LOW);
    delayMicroseconds(1);
    digitalWrite(clock_pin, HIGH);
    delayMicroseconds(1);

    byte bit = digitalRead(data_pin);

    data |= (bit << i);

  }

  //Serial.print("byte: ");
  //Serial.println(data, BIN);

  return data;
}

// Read the AS5040's angular position in [0, 1023]

int ReadPosition()
{
  unsigned int position = 0;

  //shift in our data  
  digitalWrite(selectPin, LOW);
  delayMicroseconds(1);
  byte d1 = ShiftIn(dataPin, clockPin);
  byte d2 = ShiftIn(dataPin, clockPin);
  digitalWrite(selectPin, HIGH);

  //get our position variable
  position = d1;
  position = position << 8;

  position |= d2;

  position = position >> 6;

  //check the offset compensation flag: 1 == started up
  if (!(d2 & B00100000))
    position = -1;

  //check the cordic overflow flag: 1 = error
  if (d2 & B00010000)
    position = -2;

  //check the linearity alarm: 1 = error
  if (d2 & B00001000)
    position = -3;

  //check the magnet range: B011 = error
  if ((d2 & B00000110) == B00000110)
    position = -4;

  return position;
}

//*********************************************************************************

float PIDFunction()
{
  float angle = (float)ReadPosition()*readingToRadians;
  unsigned long now = micros();
  float dA = target - angle;
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
  float pid = PIDFunction();
  float absPID = fabs(pid);
  if(absPID < deadZone)
  {
    Stop();
    return;
  }
  int pwm = round(absPID);
  if(pwm > maxPWM)
  {
    pwm = maxPWM;
  }
  if(pid < 0.0 && state == forwards)
  {
    GoBackwards(pwm);
  } else if(pid > 0.0 && state == backwards)
  {
    GoForwards(pwm);
  } else
  {
    SetSpeed(pwm);   
  }
}

void PrintState()
{
  Serial.println("\n Current state:");
  int r = ReadPosition();
  Serial.print("  Angle: ");
  Serial.print(r);
  Serial.print(", (");
  Serial.print((float)r*readingToRadians);
  Serial.print(" rads, ");
  Serial.print((float)r*readingToDegrees);
  Serial.println(" degs)");
  Serial.print("  Target angle (degrees): ");
  Serial.println(target*180.0/pi);
  Serial.print("  Dead zone (PID value): ");
  Serial.println(deadZone);
  Serial.print("  Current PID: ");
  Serial.println(PIDFunction());
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
  Serial.println(" s - Emergency stop.");
  Serial.println(" r - reset stop.");
  Serial.println(" t X - set target (X degrees).");
  Serial.println(" p - print state.");

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
  pinMode(dataPin, INPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(selectPin, OUTPUT);

  digitalWrite(clockPin, HIGH);
  digitalWrite(selectPin, HIGH);

  Stop();
  
  Serial.begin(9600);

  target = (float)ReadPosition()*readingToRadians;
  integral = 0.0;
  proportionalWeight = 1.0;
  integralWeight = 0.0;
  derivativeWeight = 0.0;
  deadZone = 1.0;
  lastTime = micros();
  maxPWM = 50;
  eStop = false;
  Prompt();
}




void loop()
{
  PID();
  
  if(Serial.available() > 0)
  {   
    char c = (char)Serial.read();
    switch(c)
    {
     case 'p':
      PrintState();
      break;
      
     case 's':
      Serial.println("Emergency stop!");
      eStop = true;
      break;

     case 'r':
      Serial.println("Emergency stop reset.");
      eStop = false;
      break;

     case 't':
      int deg = Serial.parseInt();
      target = deg*pi/180.0;
      Serial.print("Target set to ");
      Serial.print(deg);
      Serial.print(" degrees (");
      Serial.print(target);
      Serial.println(" radians).");
      break;
      
     case '?':
      Prompt();
      break;
        
     default:
      Serial.print("Unrecognised command: ");
      Serial.println(c);
      Prompt();

    }
    while(Serial.available() > 0) Serial.read();
  }
}



