#pragma once
#include <vector>
#include "oscillator.h"

Oscillator formSineWave(double frequency) {
    return formSineWave(frequency, Constant(noisemaker::maxSample));
}

template<class S>
Oscillator formSineWave(double frequency, S amplitudeSignal) {
    vector<double> waveTable = {};
    for (int i = 0; i < Oscillator::defaultWaveTableSize; i++) {
        double f = 1.0/Oscillator::defaultWaveTableSize;
        double r = sin(f * 2 * M_PI * i);
        waveTable.push_back(r);
    }
    Constant fSig = Oscillator::generateSampleThatProducesFrequency(frequency);
    Oscillator result = Oscillator(amplitudeSignal, fSig, waveTable);
    return result;
}

