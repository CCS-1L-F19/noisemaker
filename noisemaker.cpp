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

Oscillator Oscillator::sineWave(int frequency) {
    vector<double> waveTable = {};
    double periodInSamples = (double) noisemaker::sampleRate / frequency;
    for (int i= 0; i < periodInSamples; i++) {
        double cyclesPerSample = (double) frequency / noisemaker::sampleRate;
        double r = sin((cyclesPerSample) * 2 * M_PI * i);
        waveTable.push_back(r);
    }
    return Oscillator(Constant(numeric_limits<sample>::max()), Constant(1), waveTable);
}

void Oscillator::setFieldsToZero() {
    waveTable = vector<double>();
    waveTableIndex = 0;
    amplitudeSignal = NULL;
    incrementSignal = NULL;
}

// CLASS: LinearEnvelope
// TODO