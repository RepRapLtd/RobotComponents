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

#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

const float readingToRadians = 2.0*PI/1024.0;

class Encoder
{
  public:
    Encoder(int dataP, int clockP, int selectP);

    int Reading();
    float Angle();

  private:

    unsigned char ShiftIn();

    int clockPin;
    int dataPin;
    int selectPin;
};

inline float Encoder::Angle()
{
  return (float)Reading()*readingToRadians;
}

#endif
