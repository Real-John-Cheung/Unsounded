/*
    class for randomnumber
    based on this paper https://gist.github.com/bloc97/b55f684d17edd8f50df8e918cbc00f94 by B. Peng
*/

#ifndef RealRandom_h
#define RealRandom_h

#include "Arduino.h"

class RealRandom
{
public:
    RealRandom(int analogRef);
    byte random();
    unsigned int randomInt();
    float randomNormal();

private:
    int waitTime;
    int _pin;
    byte lastByte;
    byte leftStack;
    byte rightStack;
    byte rotate(byte b, int r);
    void pushLeftStack(byte bitToPush);
    void pushRightStackRight(byte bitToPush);
    float mapIntToF(long x, long in_l, long in_h, float out_l, float out_h);
};

#endif
