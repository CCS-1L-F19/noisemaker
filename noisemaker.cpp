#include "noisemaker.h"
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <limits>
#include <algorithm>
#include <vector>
#include <type_traits>
using namespace std;

namespace noisemaker {
    int sampleRate = 44100;
    int maxFrequency = sampleRate / 2;
    sample maxSample = numeric_limits<sample>::max();
    sample minSample = numeric_limits<sample>::min();
}

// ABSTRACT CLASS: Signal

sample Signal::step() {
    // Signal should only be used as an abstract class and this function
    // should never be called
    assert(false);
    return 0;
}

// CLASS: Constant

Constant::Constant(sample d) {
    value = d;
}

sample Constant::step() {
    return value;
}

// CLASS: Oscillator

template<class S1, class S2>
Oscillator::Oscillator(S1 ampSig, S2 freqSig, std::vector<double> wtab) {
    assert(wtab.size() > 0);
    setFieldsToZero();
    waveTable = wtab;
    setAmpSignal(ampSig);
    setFrequencySignal(freqSig);
}

Constant Oscillator::generateFrequencySignalWithValue(double v) {
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

Oscillator Oscillator::sineWave(double frequency) {
    return sineWave(frequency, Constant(noisemaker::maxSample));
}

template<class S>
Oscillator Oscillator::sineWave(double frequency, S amplitudeSignal) {
    vector<double> waveTable = {};
    for (int i = 0; i < defaultWaveTableSize; i++) {
        double f = 1.0/defaultWaveTableSize;
        double r = sin(f * 2 * M_PI * i);
        waveTable.push_back(r);
    }
    Constant fSig = generateFrequencySignalWithValue(frequency);
    return Oscillator(amplitudeSignal, fSig, waveTable);
}
template Oscillator Oscillator::sineWave<Constant>(double, Constant);
template Oscillator Oscillator::sineWave<Oscillator>(double, Oscillator);
template Oscillator Oscillator::sineWave<LinearEnvelope>(double, LinearEnvelope);

template <class T>
void Oscillator::setAmpSignal(T s) {
    if (amplitudeSignal != NULL) { delete amplitudeSignal; }
    bool b = std::is_base_of<Signal, T>::value;
    assert(b);
    T *p = new T(s);
    amplitudeSignal = p;
}
template void Oscillator::setAmpSignal<Constant>(Constant);
template void Oscillator::setAmpSignal<Oscillator>(Oscillator);
template void Oscillator::setAmpSignal<LinearEnvelope>(LinearEnvelope);

template <class T>
void Oscillator::setFrequencySignal(T s) {
    if (frequencySignal != NULL) { delete frequencySignal; }
    bool b = std::is_base_of<Signal, T>::value;
    assert(b);
    frequencySignal = new T(s);
}
template void Oscillator::setFrequencySignal<Constant>(Constant);
template void Oscillator::setFrequencySignal<Oscillator>(Oscillator);
template void Oscillator::setFrequencySignal<LinearEnvelope>(LinearEnvelope);

void Oscillator::setFieldsToZero() {
    waveTable = vector<double>();
    waveTableIndex = 0;
    amplitudeSignal = NULL;
    frequencySignal = NULL;
}

// CLASS: LinearEnvelope

LinearEnvelope::LinearEnvelope(vector<Phase> phasev) {
    samplesElapsed = 0;
    setPhases(phasev);
}

void LinearEnvelope::setPhases(vector<Phase> phasev) {
    phases = phasev;
    sort(phases.begin(), phases.end());
}

int LinearEnvelope::Phase::timeInSamples() {
    return time * noisemaker::sampleRate;
}

bool LinearEnvelope::Phase::operator>(Phase p) {
    return time > p.time;
}

bool LinearEnvelope::Phase::operator<(Phase p) {
    return time < p.time;
}

sample LinearEnvelope::Phase::valueInSamples() {
    return value * noisemaker::maxSample;
}

sample LinearEnvelope::step() {
    for (int i = 0; i < phases.size() - 1; i++) {
        if (samplesElapsed >= phases.back().timeInSamples()) {
                samplesElapsed++;
                return phases.back().valueInSamples();
        }
        if (samplesElapsed <= phases[i+1].timeInSamples()) {
            int phaseDurationInSamples = (phases[i+1].timeInSamples() - phases[i].timeInSamples());
            assert(phaseDurationInSamples > 0);
            sample valueDelta = phases[i+1].valueInSamples() - phases[i].valueInSamples();
            double slope = (double) valueDelta / phaseDurationInSamples;
            int distanceIntoPhase = samplesElapsed - phases[i].timeInSamples(); 
            samplesElapsed++;
            return distanceIntoPhase * slope + phases[i].valueInSamples();
        }
    }
}