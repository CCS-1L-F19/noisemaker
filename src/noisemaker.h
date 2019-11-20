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
    /**
     * The amount of samples that should be played in one second
     * by some program interpreting noisemaker's output. Default
     * value is 44100.*/
    extern int sampleRate;
    /**
     * The maximum frequency that can be represented at the current
     * sampleRate without causing aliasing. Value is `sampleRate / 2`*/
    extern int maxFrequency;
    extern sample maxSample;
    extern sample minSample;
}

class Signal {
    public:
        virtual sample step();
};
