#include <iostream>
#include <cmath>
#include <vector>
#include "noisemaker.h"
#include "fileFuncs.h"

using namespace std;

int main() {
  const int sampleRate = 11025;
  double durationInSeconds = 4.0;
  int numSamples = (int) floor(durationInSeconds * sampleRate);

  const int frequency = 440;
  const double periodInSamples = sampleRate / frequency;

  
  // Write the samples to the file
  
  sample samples[numSamples];
  vector<double> wt;
  for (int i= 0; i < periodInSamples; i++) {
      double cyclesPerSample = (double) frequency / sampleRate;
      double r = sin((cyclesPerSample) * 2 * M_PI * i);
      wt.push_back(r);
  }

  Oscillator amp = Oscillator(Constant(INT16_MAX), wt); 
  Oscillator o = Oscillator(amp, wt);

  for (int i = 0; i < numSamples; i++) {
    samples[i] = amp.step();
  }

  writeWavFile(fopen("test.wav", "w"), samples, numSamples, sampleRate);

  cout << endl;
}