/*
 * RepRap Ltd Robot Components
 * 
 * AS5040 magnetic shaft encoder
 * Adrian Bowyer
 * 
 * 31 March 2021
 * Licence: GPL
 * 
 * https://reprapltd.com
 * 
 */

#include "Encoder.h"

Encoder::Encoder(int dataP, int clockP, int selectP)
{
  dataPin = dataP;
  clockPin = clockP;
  selectPin = selectP;

  pinMode(dataPin, INPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(selectPin, OUTPUT);
  digitalWrite(clockPin, 1);
  digitalWrite(selectPin, 1);
}
 

// Read in a byte of data from the AS5040.

unsigned char Encoder::ShiftIn()
{
  byte data = 0;

  for (int i=7; i>=0; i--)
  {
    digitalWrite(clockPin, LOW);
    delayMicroseconds(1);
    digitalWrite(clockPin, HIGH);
    delayMicroseconds(1);

    unsigned char bit = digitalRead(dataPin);

    data |= (bit << i);

  }

  return data;
}

// Read the AS5040's angular position in [0, 1023]

int Encoder::Reading()
{
  unsigned int position = 0;

  //shift in our data
   
  digitalWrite(selectPin, LOW);
  delayMicroseconds(1);
  byte d1 = ShiftIn();
  byte d2 = ShiftIn();
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
