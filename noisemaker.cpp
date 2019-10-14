#include "noisemaker.h"
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <limits>
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

Oscillator Oscillator::sineWave(int frequency, Signal amplitudeSignal) {
    vector<double> waveTable = {};
    double periodInSamples = (double) noisemaker::sampleRate / frequency;
    for (int i= 0; i < periodInSamples; i++) {
        double cyclesPerSample = (double) frequency / noisemaker::sampleRate;
        double r = sin((cyclesPerSample) * 2 * M_PI * i);
        waveTable.push_back(r);
    }
    return Oscillator(amplitudeSignal, Constant(1), waveTable);
}

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
    setPhases(phasev); // also sets waveTable
}

void LinearEnvelope::setPhases(vector<Phase> phasev) {
    phases = phasev;
    // sort phases TODO
}

int LinearEnvelope::Phase::timeInSamples() {
    return time * noisemaker::sampleRate;
}

sample LinearEnvelope::step() {
    for (int i = 0; i < phases.size() - 1; i++) {
        if (samplesElapsed >= phases.back().timeInSamples()) {
                samplesElapsed++;
                return phases.back().value;
        }
        if (samplesElapsed >= phases[i].timeInSamples()) {
            int phaseDurationInSamples = (phases[i+1].timeInSamples() - phases[i].timeInSamples());
            assert(phaseDurationInSamples > 0);
            sample valueDelta = phases[i+1].value - phases[i].value;
            double slope = (double) valueDelta / phaseDurationInSamples;
            int distanceIntoPhase = samplesElapsed - phases[i].timeInSamples(); 
            samplesElapsed++;
            return distanceIntoPhase * slope + phases[i].value;
        }
    }
}