#pragma once
#include <cstdio>
#include <cstdint>
#include <cassert>
#include "noisemaker.h"

void writeWavFile(FILE *f, sample *s, int numSamples, int sampleRate);