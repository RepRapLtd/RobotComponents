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
const int forwards = 1;                         // What to write to the motor to make the output go clockwise
const float pi = 3.1415926;
const float readingToRadians = 2.0*pi/1024.0;

//***********************************************************************************

// Motor control

void GoForwards(int pwm)
{
  digitalWrite(pWMPin, 0);
  digitalWrite(dirPin, forwards);
  delay(1);
  analogWrite(pWMPin, pwm);  
}

void GoBackwards(int pwm)
{
  digitalWrite(pWMPin, 0);
  digitalWrite(dirPin, 1 - forwards);
  delay(1);
  analogWrite(pWMPin, pwm);  
}

void Stop()
{
  analogWrite(pWMPin, 0);  
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

  Serial.begin(9600);
  GoForwards(5);
}

void loop()
{
   int reading = ReadPosition();
   
   if (reading >= 0)
   {
      float angle = (float)reading*readingToRadians;
      Serial.print(" A: ");
      Serial.println(angle);
   }
   else
   {
      Serial.print("Error: ");
      Serial.println(reading);
   }
   
   delay(100);
}



