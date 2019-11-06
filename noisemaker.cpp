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
}

sample Signal::step() {
    // FOR SOME REASON THE ENVELOPE SIGNAL THAT IS PASSED TO
    // AN OSCILLATOR IN THE TESTS CALLS THIS FUNCTION INSTEAD
    // OF ITS OWN
    assert(false);
    return 0;
}

// CLASS: Constant

Constant::Constant(int i) {
    value = i;
}

sample Constant::step() {
    return value;
}

// CLASS: Oscillator

template<class S1, class S2>
Oscillator::Oscillator(S1 ampSig, S2 incSig, std::vector<double> wtab) {
    setFieldsToZero();
    waveTable = wtab;
    setAmpSignal(ampSig);
    setIncrementSignal(incSig);
}

sample Oscillator::step() {
    int a = amplitudeSignal->step();
    int i = incrementSignal->step();
    if (waveTableIndex >= waveTable.size()) {
        waveTableIndex %= waveTable.size();
    }
    sample result = a * waveTable[waveTableIndex];
    waveTableIndex += i;
    return result;
}

template<class S>
Oscillator Oscillator::sineWave(double frequency, S amplitudeSignal) {
    vector<double> waveTable = {};
    double periodInSamples = (double) noisemaker::sampleRate / frequency;
    for (int i= 0; i < periodInSamples; i++) {
        double cyclesPerSample = (double) frequency / noisemaker::sampleRate;
        double r = sin((cyclesPerSample) * 2 * M_PI * i);
        waveTable.push_back(r);
    }
    return Oscillator(amplitudeSignal, Constant(1), waveTable);
}
template Oscillator Oscillator::sineWave<Constant>(double, Constant);
template Oscillator Oscillator::sineWave<Oscillator>(double, Oscillator);
template Oscillator Oscillator::sineWave<LinearEnvelope>(double, LinearEnvelope);

template <class T>
void Oscillator::setAmpSignal(T s) {
    if (amplitudeSignal != NULL) { delete amplitudeSignal; }
        bool b = std::is_base_of<Signal, T>::value;
        assert(b);
        amplitudeSignal = new T(s);
}
template void Oscillator::setAmpSignal<Constant>(Constant);
template void Oscillator::setAmpSignal<Oscillator>(Oscillator);
template void Oscillator::setAmpSignal<LinearEnvelope>(LinearEnvelope);

template <class T>
void Oscillator::setIncrementSignal(T s) {
    if (incrementSignal != NULL) { delete incrementSignal; }
        bool b = std::is_base_of<Signal, T>::value;
        assert(b);
        incrementSignal = new T(s);
}
template void Oscillator::setIncrementSignal<Constant>(Constant);
template void Oscillator::setIncrementSignal<Oscillator>(Oscillator);
template void Oscillator::setIncrementSignal<LinearEnvelope>(LinearEnvelope);

void Oscillator::setFieldsToZero() {
    waveTable = vector<double>();
    waveTableIndex = 0;
    amplitudeSignal = NULL;
    incrementSignal = NULL;
}

// CLASS: LinearEnvelope
// TODO

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
    return value > p.value;
}

bool LinearEnvelope::Phase::operator<(Phase p) {
    return value < p.value;
}

sample LinearEnvelope::Phase::valueInSamples() {
    return value * numeric_limits<sample>::max();
}

sample LinearEnvelope::step() {
    for (int i = 0; i < phases.size() - 1; i++) {
        if (samplesElapsed >= phases.back().timeInSamples()) {
                samplesElapsed++;
                return phases.back().valueInSamples();
        }
        if (samplesElapsed >= phases[i].timeInSamples()) {
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