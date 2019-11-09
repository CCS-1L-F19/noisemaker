// high level overview: Oscillators create sound
// all time values are in units of samples

#pragma once

#include <vector>
#include <limits>
#include <cassert>
#include <cinttypes>

typedef double sample;
typedef int16_t writableSample;

namespace noisemaker {
    extern int sampleRate;
    extern int maxFrequency;
    extern sample maxSample;
    extern sample minSample;
}

class Signal {
    public:
        virtual sample step();
};
