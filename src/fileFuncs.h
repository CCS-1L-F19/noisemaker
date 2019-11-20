#pragma once
#include <cstdio>
#include <cstdint>
#include <cassert>
#include "noisemaker.h"

/**
 * Writes the contents of `s` to FILE f. Usually you will have to cast
 * your array of samples to an array of writableSamples before passing
 * it to writeWavFile */
void writeWavFile(FILE *f, writableSample *s, int numSamples, int sampleRate);