/*
    Use Arduino IDE to complie and burn the code to the micro controller
    This file assume that a Arduino Nano v.3 board is used
    For hardware design and setup, visit https://github.com/Real-John-Cheung/Unsounded 
    Code by JohnC (me@johncheung.art)
    The random number generator is based on this paper https://gist.github.com/bloc97/b55f684d17edd8f50df8e918cbc00f94 by B. Peng
    This file is licensed under GNU GPLv3 
*/

#include "RealRandom.h"


int floatPin = A0;

RealRandom rangen(floatPin);

void setup() {
}

void loop(){

}

