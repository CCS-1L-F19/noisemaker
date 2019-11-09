#include <iostream>
#include <cmath>
#include <vector>
#include "noisemaker.h"
#include "fileFuncs.h"
#include "adder.h"
#include "multiplier.h"
#include "oscillator.h"
#include "constant.h"
#include "premadeSignals.h"

using namespace std;

int main() {
  noisemaker::sampleRate = 44100;
  double durationInSeconds = 4.0;
  int numSamples = (int) floor(durationInSeconds * noisemaker::sampleRate);
  writableSample samples[numSamples];
 
  Multiplier output;
  output.signals.push_back(new Oscillator(formSineWave(440, Constant(200))));
  output.signals.push_back(new Oscillator(formSineWave(50, Constant(100))));

  for (int i = 0; i < numSamples; i++) {
    samples[i] = (writableSample) output.step();
  }

  writeWavFile(fopen("test.wav", "w"), samples, numSamples, noisemaker::sampleRate);

  cout << endl;
}