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

  Constant c(noisemaker::maxSample*.5);
  Oscillator o = Oscillator::sineWave(3);
  #define WIS Adder::WeightedInputSignal
  Adder a = Adder({WIS(c, 1), WIS(o, .5)}, false);
  #undef WIS

  Oscillator realboi = Oscillator::sineWave(440);
  realboi.setFrequencySignal(a);

  for (int i = 0; i < numSamples; i++) {
    samples[i] = realboi.step();
  }

  writeWavFile(fopen("test.wav", "w"), samples, numSamples, noisemaker::sampleRate);

  cout << endl;
}