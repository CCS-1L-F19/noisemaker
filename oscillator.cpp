#pragma once

#include "oscillator.h"
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <type_traits>
using namespace std;

template<class S1, class S2>
Oscillator::Oscillator(S1 ampSig, S2 freqSig, std::vector<double> wtab) {
    assert(wtab.size() > 0);
    setFieldsToZero();
    waveTable = wtab;
    setAmpSignal(ampSig);
    setFrequencySignal(freqSig);
}

Oscillator::Oscillator() : amplitudeSignal(NULL), frequencySignal(NULL), waveTableIndex(0) {}

sample Oscillator::generateFrequencySignalWithValue(double v) {
    double ratio = v / noisemaker::maxFrequency;
    return ratio * noisemaker::maxSample;
}

double Oscillator::interpretFrequencySignalValue(sample v) {
    double ratio = (double) v / noisemaker::maxSample;
    return ratio * noisemaker::maxFrequency;
}

double Oscillator::getIncrementValueForFrequency(double f) {
    double periodInSamples = noisemaker::sampleRate / f;
    return waveTable.size() / periodInSamples;    
}

double Oscillator::getIncrementValueFromFrequencySignalValue(sample s) {
    return getIncrementValueForFrequency(interpretFrequencySignalValue(s));
}

sample Oscillator::step() {
    int amp = amplitudeSignal->step();
    double inc = getIncrementValueFromFrequencySignalValue(frequencySignal->step());
    while (waveTableIndex > waveTable.size()) {
        waveTableIndex -= waveTable.size();
    }
    sample result = amp * waveTable[waveTableIndex];
    waveTableIndex += inc;
    return result;
}


template <class T>
void Oscillator::setAmpSignal(T s) {
    if (amplitudeSignal != NULL) { delete amplitudeSignal; }
    bool b = std::is_base_of<Signal, T>::value;
    assert(b);
    T *p = new T(s);
    amplitudeSignal = p;
}

template <class T>
void Oscillator::setFrequencySignal(T s) {
    if (frequencySignal != NULL) { delete frequencySignal; }
    bool b = std::is_base_of<Signal, T>::value;
    assert(b);
    frequencySignal = new T(s);
}

void Oscillator::setFieldsToZero() {
    waveTable = vector<double>();
    waveTableIndex = 0;
    amplitudeSignal = NULL;
    frequencySignal = NULL;
}

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
    Constant fSig = Oscillator::generateFrequencySignalWithValue(frequency);
    Oscillator result = Oscillator(amplitudeSignal, fSig, waveTable);
    return result;
}