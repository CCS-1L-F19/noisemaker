#include <iostream>
#include <cmath>
#include <vector>
#include "noisemaker.h"
#include "fileFuncs.h"

using namespace std;

int main() {
  noisemaker::sampleRate = 44100;
  double durationInSeconds = 4.0;
  int numSamples = (int) floor(durationInSeconds * noisemaker::sampleRate);
 
  sample samples[numSamples];
  Constant c(noisemaker::maxSample*.5);
  Oscillator o = Oscillator::sineWave(440);
  Adder::WeightedInputSignal s1;
  s1.setSignal()
  // TRYING TO MAKE AN ADDER
  vector<Adder::WeightedInputSignal> sigs = {{.5, o}, {.5, c}};
  Adder a = Adder(sigs);

  for (int i = 0; i < numSamples; i++) {
    samples[i] = a.step();
  }

  writeWavFile(fopen("test.wav", "w"), samples, numSamples, noisemaker::sampleRate);

  cout << endl;
}