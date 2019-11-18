#pragma once
#include <vector>
#include "oscillator.h"
#include "adder.h"

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

Oscillator formSineWave(double frequency) {
    return formSineWave(frequency, Constant(noisemaker::maxSample));
}

Adder formVibratoFreqSignal(double baseFrequency, double vibratoFrequency, double vibratoMagnitude) {
  sample base = Oscillator().generateSampleThatProducesFrequency(baseFrequency);
  Constant vibratoBase(base);
  sample vibratoDeltaAmplitude = Oscillator().generateSampleThatProducesFrequency(vibratoMagnitude);
  Oscillator vibratoDelta = formSineWave(vibratoFrequency, Constant(vibratoDeltaAmplitude));
  return Adder({{vibratoBase, 1}, {vibratoDelta, 1}}, false);
}

template<class S>
Oscillator formVibratoSineWave(double baseFrequency, double vibratoFrequency, double vibratoMagnitude, S ampSignal) {
    Oscillator result = formSineWave(0, ampSignal);
    result.setFrequencySignal(formVibratoFreqSignal(baseFrequency, vibratoFrequency, vibratoMagnitude));
    return result;
}

