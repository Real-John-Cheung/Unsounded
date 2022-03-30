/*
    class for randomnumber
    based on this paper https://gist.github.com/bloc97/b55f684d17edd8f50df8e918cbc00f94 by B. Peng
*/

#include "RealRandom.h"
#include "Arduino.h"

RealRandom::RealRandom(int analogRef)
{
    _pin = analogRef;
    waitTime = 16;
    lastByte = 0;
    leftStack = 0;
    rightStack = 0;
}

byte RealRandom::rotate(byte b, int r)
{
    return (b << r) | (b >> (8 - r));
}

void RealRandom:: pushLeftStack(byte bitToPush)
{
    leftStack = (leftStack << 1) ^ bitToPush ^ leftStack;
}

void RealRandom::pushRightStackRight(byte bitToPush)
{
    rightStack = (rightStack >> 1) ^ (bitToPush << 7) ^ rightStack;
}

byte RealRandom::random() {
    byte finalByte = 0;
    byte lastStack = leftStack ^ rightStack;
    for (int i = 0; i < 4; i++)
    {
        delayMicroseconds(waitTime);
        int leftBits = analogRead(_pin);
        delayMicroseconds(waitTime);
        int rightBits = analogRead(_pin);

        finalByte ^= rotate(leftBits, i);
        finalByte ^= rotate(rightBits, 7 - i);
        
        for (int j = 0; j < 8; j++)
        {
            byte leftBit = (leftBits >> j) & 1;
            byte rightBit = (rightBits >> j) & 1;
            if (leftBit != rightBit) {
                if (lastStack % 2 == 0) {
                    pushLeftStack(leftBit);
                } else {
                    pushRightStackRight(leftBit);
                }
            }
        }
    }

    lastByte ^= (lastByte >> 3) ^ (lastByte << 5) ^ (lastByte >> 4);
    lastByte ^= finalByte;
  
    return lastByte ^ leftStack ^ rightStack;
}

unsigned int RealRandom::randomInt(){
    byte a = random();
    byte b = random();
    return a | (b << 8);
}

float RealRandom::randomNormal(){
    unsigned int a = randomInt();
    return mapIntToF(a, 65535, 0, 1.0, 0.0);
}

float RealRandom::mapIntToF(int x, int in_h, int in_l, float out_h, float out_l){
    return ((float)(x - in_h)) * (out_h - out_l) / ((float)(in_h - in_l)) + out_l;
}