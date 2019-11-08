#include <iostream>
#include <cmath>
#include <vector>
#include "noisemaker.h"
#include "fileFuncs.h"
#include "adder.h"
#include "oscillator.h"
#include "constant.h"

using namespace std;

int main() {
  noisemaker::sampleRate = 44100;
  double durationInSeconds = 4.0;
  int numSamples = (int) floor(durationInSeconds * noisemaker::sampleRate);
 
  sample samples[numSamples];

  // VIBRATO DEMO:

  Oscillator output = formSineWave();

  Oscillator vibratoDelta = formSineWave(30);
  // need to multiply vibratoDelta by something to make it a lot smaller
  sample d = output.generateSampleThatProducesFrequency(440);
  Constant vibratoBase(d);
  Adder vibratoFrequency = Adder({{vibratoBase, 1}, {vibratoDelta, (d * 0.3) / noisemaker::maxSample}}, false);
  // Adder vibratoFrequency = Adder({WIS(vibratoBase, 1)}, false);

  output.setFrequencySignal(vibratoFrequency);
  output.setAmpSignal(Constant(noisemaker::maxSample));

  // CHORD DEMO

  // Oscillator root = formSineWave(440);
  // Oscillator M3 = formSineWave(523);
  // Oscillator P5 = formSineWave(660);
  // Oscillator M7 = formSineWave(784);
  // #define WIS Adder::WeightedInputSignal
  // Adder output({WIS(root, .4), WIS(M3, .1), WIS(P5, .2), WIS(M7, .1)});
  // #undef WIS

  for (int i = 0; i < numSamples; i++) {
    samples[i] = output.step();
  }

  writeWavFile(fopen("test.wav", "w"), samples, numSamples, noisemaker::sampleRate);

  cout << endl;
}