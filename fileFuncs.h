#include <cstdio>
#include <cstdint>
#include <cassert>
#include "noisemaker.h"

void writeWavHeaderFile(FILE *f, sample *s, int numSamples, int sampleRate);