#pragma once
#include "oscillator.h"
#include "adder.h"

Oscillator formSineWave(double frequency = 0);

template<class S>
Oscillator formSineWave(double frequency, S amplitudeSignal);


template<class S>
Oscillator formVibratoSineWave(double baseFrequency, double vibratoFrequency,
                               double vibratoMagnitude, S ampSignal);


Adder formVibratoFreqSignal(double baseFrequency, double vibratoFrequency, double vibratoMagnitude);

#include "premadeSignals.cpp"