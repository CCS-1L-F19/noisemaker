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

  const int frequency = 440;
  const double periodInSamples = noisemaker::sampleRate / frequency;

  // Write the samples to the file
  
  sample samples[numSamples];
  vector<double> wt;
  for (int i= 0; i < periodInSamples; i++) {
      double cyclesPerSample = (double) frequency / noisemaker::sampleRate;
      double r = sin((cyclesPerSample) * 2 * M_PI * i);
      wt.push_back(r);
  }
  // Oscillator amp = Oscillator::sineWave(440);
  Oscillator o = Oscillator(Oscillator::sineWave(2), Constant(1), wt);

  for (int i = 0; i < numSamples; i++) {
    samples[i] = o.step();
  }

  writeWavFile(fopen("test.wav", "w"), samples, numSamples, noisemaker::sampleRate);

  cout << endl;
}