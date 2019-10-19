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
  // LinearEnvelope e = LinearEnvelope({{0,0}, {1,.2}, {.1,.5}, {.05,3.5}, {0,4}});

  // THIS IS A HELICOPTER
  // Oscillator fo = Oscillator::sineWave(20, Constant(200));
  Oscillator o = Oscillator::sineWave();
  // o.setFrequencySignal(fo);

  for (int i = 0; i < numSamples; i++) {
    samples[i] = o.step();
  }

  writeWavFile(fopen("test.wav", "w"), samples, numSamples, noisemaker::sampleRate);

  cout << endl;
}