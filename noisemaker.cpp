#include "noisemaker.h"
#include <containers>
#include <string>
using namespace std;

sample Oscillator::getSampleAtTime(int t) {
    return waveform[(t * sampleIncrement) % (waveTableLength)];
}

void Oscillator::setWaveform(sample samples[], int size) {
    if (waveTable != NULL) { delete waveform; }

    waveform = new sample[size];
    memcpy(waveform, samples, size);

    waveTableLength = size;
}