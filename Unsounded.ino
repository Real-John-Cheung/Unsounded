/*
    Use Arduino IDE to complie and burn the code to the micro controller
    This file assume that a Arduino Nano v.3 board is used
    For hardware design and setup, visit https://github.com/Real-John-Cheung/Unsounded
    Code by JohnC (me@johncheung.art)
    The random number generator is based on this paper https://gist.github.com/bloc97/b55f684d17edd8f50df8e918cbc00f94 by B. Peng
    Using LowPower library v2.2.0 by LowPowerLab https://github.com/LowPowerLab/LowPower
    This file is licensed under GNU GPLv3
*/

#include "RealRandom.h"
#include "LowPower.h"

int floatPin = A0; // TBD
int trigger = 7;   // TBD

float cu;
int th = 80;

RealRandom rangen(floatPin);

void setup()
{
  pinMode(trigger, OUTPUT);
  digitalWrite(trigger, HIGH);
  cu = rangen.randomNormal() * 10;
}

void loop()
{
  cu += rangen.randomNormal() * 2;
  if (cu > th) {
    trig(1000 + map(rangen.randomInt(), 0, 65535, 500, 1500));
    cu = rangen.randomNormal() * 10;
  }
  for (int i = 0; i < 10; i++)
  {
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  }
}

void trig(int t) {
  digitalWrite(trigger, LOW);
  delay(t);
  digitalWrite(trigger, HIGH);
}
