#include <iostream>
#include <cmath>
#include "noisemaker.h"
#include "fileFuncs.h"

using namespace std;

int main() {
  const int sampleRate = 11025;
  double durationInSeconds = 4.0;
  int numSamples = (int) floor(durationInSeconds * sampleRate);

  const int frequency = 440;
  
  // Write the samples to the file
  
  sample samples[numSamples];
  for (int i=0; i<numSamples; i++) {
      samples[i] = INT16_MAX * sin(frequency * 2 * M_PI * (i / (double) sampleRate));
  }
  writeWavFile(fopen("test.wav", "w"), samples, numSamples, sampleRate);

  cout << endl;
}