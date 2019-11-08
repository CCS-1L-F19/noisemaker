#pragma once
#include "oscillator.h"
#include "adder.h"

Oscillator formSineWave(double frequency = 0);

template<class S>
Oscillator formSineWave(double frequency, S amplitudeSignal);



#include "premadeSignals.cpp"