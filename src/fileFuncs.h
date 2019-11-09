#pragma once
#include <cstdio>
#include <cstdint>
#include <cassert>
#include "noisemaker.h"

void writeWavFile(FILE *f, writableSample *s, int numSamples, int sampleRate);