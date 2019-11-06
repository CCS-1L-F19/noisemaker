#include "noisemaker.h"
#include <cstring>
using namespace std;

sample Oscillator::getSampleAtTime(int t) {
    return waveTable[(t * sampleIncrement) % (waveTableLength)];
}

void Oscillator::setWaveform(sample samples[], int size) {
    if (waveTable != NULL) { delete waveTable; }

    waveTable = new sample[size];
    memcpy(waveTable, samples, size);

    waveTableLength = size;
}