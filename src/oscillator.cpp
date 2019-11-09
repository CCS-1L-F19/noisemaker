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

sample Oscillator::generateSampleThatProducesFrequency(double v) {
    double ratio = v / noisemaker::maxFrequency;
    return ratio * noisemaker::maxSample;
}

double Oscillator::interpretFrequencySample(sample v) {
    double ratio = (double) v / noisemaker::maxSample;
    return ratio * noisemaker::maxFrequency;
}

double Oscillator::getIncrementValueForFrequency(double f) {
    double periodInSamples = noisemaker::sampleRate / f;
    return waveTable.size() / periodInSamples;    
}

double Oscillator::getIncrementValueFromFrequencySample(sample s) {
    return getIncrementValueForFrequency(interpretFrequencySample(s));
}

sample Oscillator::step() {
    int amp = amplitudeSignal->step();
    double inc = getIncrementValueFromFrequencySample(frequencySignal->step());
    while (waveTableIndex > waveTable.size()) {
        waveTableIndex -= waveTable.size();
    }
    double junk;
    double weightedLeftSample = modf(waveTableIndex, &junk) * waveTable[waveTableIndex];
    double weightedRightSample = (1-modf(waveTableIndex, &junk)) * waveTable[(int)(waveTableIndex + 1) % waveTable.size()];
    sample result = amp * (weightedLeftSample + weightedRightSample);
    waveTableIndex += inc;
    return result;
}


template <class T>
void Oscillator::setAmpSignal(T s) {
    if (amplitudeSignal != NULL) { delete amplitudeSignal; }
    static_assert(is_base_of<Signal, T>::value, "setAmpSignal only accepts arguments of type Signal.");
    T *p = new T(s);
    amplitudeSignal = p;
}

template <class T>
void Oscillator::setFrequencySignal(T s) {
    if (frequencySignal != NULL) { delete frequencySignal; }
    static_assert(is_base_of<Signal, T>::value, "setFrequencySignal only accepts arguments of type Signal.");
    frequencySignal = new T(s);
}

void Oscillator::setFieldsToZero() {
    waveTable = vector<double>();
    waveTableIndex = 0;
    amplitudeSignal = NULL;
    frequencySignal = NULL;
}

